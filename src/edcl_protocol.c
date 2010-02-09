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

/**
 * Send an edcl paquet and fragment it if max_paquet_size < data_size
 */
static int		send_fragmented(void)
{
  unsigned int		address_offset = 0;
  unsigned int		nb_sent_paquet = 0;
  unsigned int		local_data_size = config.data_size;
  edcl_paquet_t*	paquet = NULL;
  
  /* Allocating the paquet of the paquet */
  paquet =
    calloc(1, min(local_data_size, MAX_DATA_SIZE) + sizeof (edcl_header_t));
  if (paquet == NULL)
    goto error_malloc;

  do 
  {
    /* Filling up the edcl header */
    clear_header(paquet->header);
    set_operation(paquet->header, WRITE_OP);
    set_address(paquet->header, config.memory_address + address_offset);
    set_length(paquet->header, min(local_data_size, MAX_DATA_SIZE));
    if (config.verbose)
      printf("\t %d paquet has a size of: %do.\n", 
	     nb_sent_paquet, 
	     min(local_data_size, MAX_DATA_SIZE));

    /* Copying the data in the paquet */
    memcpy(paquet->data,
	   config.data + address_offset, 
	   min(local_data_size, MAX_DATA_SIZE));

    /* Sending the paquet to the ethernet IP */
    if (send(config.socket, 
	     paquet,
	     min(local_data_size, MAX_DATA_SIZE) + sizeof (edcl_header_t), 0)
	== -1)
      goto error_send;

    address_offset += min(local_data_size, MAX_DATA_SIZE);
    local_data_size -= min(local_data_size, MAX_DATA_SIZE); 
    ++nb_sent_paquet;
  } while (local_data_size > 0);

  if (config.verbose)
    printf("The file has been fragmented in %d paquets.\n", nb_sent_paquet);

  /* Releasing ressources */
  free(paquet);

  return (0);

 error_send:
  if (config.verbose)
    printf("Error while sending the paquet.\n");
  free(paquet);
  return (-1);
 error_malloc:
  if (config.verbose)
    printf("Unable to allocate the paquet.\n");
  return (-1);
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

/**
 * Send a file to be written at config.memory_address
 */
int			send_file(void)
{
  FILE*			fd = NULL;

  /* Open the file */
  if ((fd = fopen(config.filename, "r")) == NULL)
    {
      printf("Error opening file %s.\n", config.filename);
      goto error_fopen;
    }
  if (config.verbose)
    printf("File %s has been opened.\n", config.filename);

  /* Retreive file size */
  get_file_size(&(config.data_size), fd);
  if (config.verbose)
    printf("File size is: %d\n", config.data_size);

  /* Copy the file in memory */
  if ((config.data = calloc(1, config.data_size + sizeof (edcl_header_t))) == NULL)
    {
      printf("Error allocating memory.\n");
      goto error_malloc;
    }
  fread(config.data, 1, config.data_size, fd);
  if (config.verbose)
    printf("File has been copied in memory.\n");

  /* Swap the file bytes if necessary */
  if (config.big_endian)
    swap_bytes(config.data, config.data_size / 4);

  /* Send the file over the socket */
  if (send_fragmented() != 0)
    goto error_send;
  if (config.verbose)
    printf("File has been sent to the ethernet IP.\n");

  /* Release ressources */
  free(config.data);
  fclose(fd);

  return (0);

 error_send:
  printf("Erreur lors de l'envoie du paquet.\n");
  free(config.data);
 error_malloc:
  printf("Erreur lors de l'allocation des données.\n");
  fclose(fd);
 error_fopen:
  return (errno);
}
