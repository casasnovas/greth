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
 * Convert bytes from little endian to big endian
 *
 * data: a pointer to an array of int to be swapped
 * data_size: number of elements to be swapped
 */
static void		swap_bytes(unsigned int*	data_i,
				   unsigned int		data_size)
{
  unsigned int		i = 0;

  for (i = 0; i < data_size; ++i)
    data_i[i] = to_big_endian_32(data_i[i]);
}

/**
 * Send a file to be written in dram
 */
int			send_file(void)
{
  FILE*			fd = NULL;
  unsigned int		file_size = 0;

  /* Open the file */
  if ((fd = fopen(config.filename, "r")) == NULL)
    {
      printf("Error opening file %s.\n", config.filename);
      goto error_fopen;
    }
  if (config.verbose)
    printf("File %s has been opened.\n", config.filename);

  get_file_size(file_size, fd);
  if (config.verbose)
    printf("File size is: %d\t = 0x%08x \n", file_size, file_size);

  /* Copy the file in memory */
  if ((config.buffer = calloc(1, file_size + sizeof (edcl_header_t))) == NULL)
    {
      printf("Error allocating memory.\n");
      goto error_malloc;
    }
  fread(config.paquet->data_i, 1, file_size, fd);
  if (config.verbose)
    printf("File has been copied in memory.\n");

  /* Fill the edcl header and swap to big endian (if big_endian flag is set) */
  set_operation(config.paquet->header, WRITE_OP);
  set_address(config.paquet->header, config.memory_address);
  set_length(config.paquet->header, file_size);
  if (config.big_endian)
    swap_bytes(config.paquet->data_i, file_size / 4);

  /* Send the file over the socket */
  if (send(config.socket,
	   config.buffer,
	   file_size + sizeof (edcl_header_t),
	   0) == -1)
    goto error_send;
  if (config.verbose)
    printf("File has been sent to the ethernet IP.\n");

  /* Release ressources */
  free(config.buffer);
  fclose(fd);

  return (0);

 error_send:
  printf("Erreur lors de l'envoie du paquet.\n");
  free(config.buffer);
 error_malloc:
  printf("Erreur lors de l'allocation des données.\n");
  fclose(fd);
 error_fopen:
  return (errno);
}
