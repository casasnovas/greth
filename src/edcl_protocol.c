/*
    (c) Quentin Casasnovas (quentin.casasnovas@gmail.com)

    This file is part of greth.

    greth is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    greth is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with greth. If not, see <http://www.gnu.org/licenses/>.
*/

#include "edcl_protocol.h"

static inline void	treat_aknowledgment(edcl_packet_t*	packet,
					    unsigned int*	offset,		
					    unsigned int*	size,
					    unsigned int*	sequence,
					    unsigned int*	nb_ack)
		
{
  /* We've been aknowledge, keep sending */
  if (get_ack(packet->header))
    {
      *offset += min(*size, MAX_DATA_SIZE);
      *size -= min(*size, MAX_DATA_SIZE);
      ++(*sequence);
      ++(*nb_ack);
    }
  /* The sequence number was wrong, fix it */
  else
    {
      if (config.verbose)
	fprintf(stderr,
		"  Wrong sequence number (%d) should be: %d.\n",
	       *sequence, get_sequence(packet->header));
      *sequence = get_sequence(packet->header);
    }
}

/**
 * Send an edcl packet and fragment it if max_packet_size < data_size
 */
static int		send_fragmented(void)
{
  unsigned int		nb_ack_packet = 0;
  unsigned int		address_offset = 0;
  unsigned int		nb_sent_packet = 0;
  unsigned int		sequence_number = 0;
  unsigned int		local_data_size = config.data_size;
  edcl_packet_t*	packet = NULL;

  /* Allocating the packet of the packet */
  packet =
    calloc(1, min(local_data_size, MAX_DATA_SIZE) + sizeof (edcl_header_t));
  if (packet == NULL)
    goto error_malloc;

  do
  {
    /* Filling up the edcl header */
    clear_header(packet->header);
    set_operation(packet->header, WRITE_OP);
    set_sequence(packet->header, sequence_number);
    set_address(packet->header, config.memory_address + address_offset);
    set_length(packet->header, min(local_data_size, MAX_DATA_SIZE));

    if (config.verbose)
      fprintf(stderr,
	      " Trying to write at 0x%08x.\n", config.memory_address + address_offset);

    /* Copying the data in the packet */
    memcpy(packet->data,
	   config.data_c + address_offset,
	   min(local_data_size, MAX_DATA_SIZE));

    /* Sending the packet to the ethernet IP */
    if (sendto(config.socket,
	       packet,
	       min(local_data_size, MAX_DATA_SIZE) + sizeof (edcl_header_t),
	       0, config.serv_info->ai_addr, config.serv_info->ai_addrlen)
	== -1)
      goto error_send;

    /* Waiting for the aknowledgment */
    if (recvfrom(config.socket,  packet,
    		 sizeof (edcl_header_t) + min(local_data_size, MAX_DATA_SIZE),
    		 0, NULL, 0) == -1)
      goto error_recvfrom;

  /* We've been aknowledge, keep sending */
  if (get_ack(packet->header))
    {
      address_offset += min(local_data_size, MAX_DATA_SIZE);
      local_data_size -= min(local_data_size, MAX_DATA_SIZE);
      ++sequence;
      ++nb_ack;
    }
  /* The sequence number was wrong, fix it */
  else
    {
      if (config.verbose)
	fprintf(stderr,
		"  Wrong sequence number (%d) should be: %d.\n",
		sequence, get_sequence(packet->header));
      sequence = get_sequence(packet->header);
    }

    ++nb_sent_packet;
  } while (local_data_size > 0);

  if (config.verbose)
    {
      fprintf(stderr,
	      "The datas have been fragmented in %d packets.\n", nb_ack_packet);
      fprintf(stderr,
	      "\t %d packets have been sent (%d have been lost).\n",
	     nb_sent_packet,
	     nb_sent_packet - nb_ack_packet);
    }

  /* Releasing ressources */
  free(packet);

  return (0);

 error_recvfrom:
 error_send:
  if (config.verbose)
    fprintf(stderr,
	    "Error while sending the packet.\n");
  free(packet);
  return (errno);
 error_malloc:
  if (config.verbose)
    fprintf(stderr,
	    "Unable to allocate the packet.\n");
  return (errno);
}

/**
 * Convert bytes from little endian to big endian
 *
 * data: a pointer to an array of int to be swapped
 * data_size: number of elements to be swapped
 */
static inline void	swap_bytes(unsigned int*	data_i,
				   unsigned int		data_size)
{
  unsigned int		i = 0;

  for (i = 0; i < data_size; ++i)
    data_i[i] = to_big_endian_32(data_i[i]);

  if (config.verbose)
    fprintf(stderr,
	    "Bytes have been swapped to big endian.\n");
}

/**
 * Retreive the size of the file pointed to by fd and store it in
 * file_size. file_size will always be a multiple of 4 so file_size may be
 * bigger than the real file_size.
 *
 * file_size: a pointer where to store the real file size.
 * fd: a file descriptor which points to the file we're probing the size
 */
static inline void	get_file_size(unsigned int*	file_size,
				      FILE*		fd)
{
  fseek(fd, 0, SEEK_END);
  *file_size = (unsigned int) ftell(fd);
  rewind(fd);

  /* We assure that file_size % 4 == 0 */
  if (*file_size & 0x3)
    *file_size = (*file_size + 0x4) & ~0x3;
}

int			send_word(void)
{
  /* We're sending a dword, so data_size is always 4 */
  config.data_size = 4;
  if (!(config.big_endian))
    config.word = to_big_endian_32(config.word);
  config.data = &(config.word);

  /* Send the word over the socket*/
  if (send_fragmented() != 0)
    goto error_send;

  return (0);

 error_send:
  fprintf(stderr,
	  "Unable to send the word.\n");
  return (errno);
}

/**
 * Send a file to be written at config.memory_address
 */
int			send_file(void)
{
  FILE*			fd = NULL;

  /* Open the file */
  if ((fd = fopen(config.filename, "r")) == NULL)
    {
      fprintf(stderr,
	      "Error opening file %s.\n", config.filename);
      goto error_fopen;
    }
  if (config.verbose)
    fprintf(stderr,
	    "File %s has been opened.\n", config.filename);

  /* Retreive file size */
  get_file_size(&(config.data_size), fd);
  if (config.verbose)
    fprintf(stderr,
	    "File size is: %d\n", config.data_size);

  /* Copy the file in memory */
  if ((config.data = calloc(1, config.data_size + sizeof (edcl_header_t))) == NULL)
    {
      fprintf(stderr,
	      "Error allocating memory.\n");
      goto error_malloc;
    }
  fread(config.data, 1, config.data_size, fd);
  if (config.verbose)
    fprintf(stderr,
	    "File has been copied in memory.\n");

  /* Swap the file bytes if necessary */
  if (config.big_endian)
    swap_bytes(config.data, config.data_size / 4);

  /* Send the file over the socket */
  if (send_fragmented() != 0)
    goto error_send;
  if (config.verbose)
    fprintf(stderr,
	    "File has been sent to the ethernet IP.\n");

  /* Release ressources */
  free(config.data);
  fclose(fd);

  return (0);

 error_send:
  fprintf(stderr,
	  "Error when sending the file.\n");
  free(config.data);
 error_malloc:
  fprintf(stderr,
	  "Unable to allocate a packet.\n");
  fclose(fd);
 error_fopen:
  return (errno);
}
