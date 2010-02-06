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

static void		swap_bytes(unsigned int filesize)
{
  unsigned int		i = 0;
  unsigned int*		buffer_i = 
    (unsigned int*) (config.buffer_c + sizeof (edcl_paquet_t));

  for (i = 0; i < (filesize / 4); ++i)
    buffer_i[i] = to_big_endian(buffer_i[i]);
}

/**
 * Send a file to be written in dram
 */
int			send_file(void)
{
  FILE*			fd = NULL;
  unsigned int		file_size = 0;
  edcl_paquet_t*	edcl_paquet = NULL;

  /* Open the file */
  if ((fd = fopen(config.filename, "r")) == NULL)
    {
      printf("Error opening file %s.\n", config.filename);
      goto error_fopen;
    }
  if (config.verbose)
    printf("File %s has been opened.\n", config.filename);

  get_file_size(file_size, fd);

  /* Copy the file in memory */
  if ((config.buffer = calloc(1, file_size + sizeof (edcl_paquet_t))) == NULL)
    {
      printf("Error allocating memory.\n");
      goto error_malloc;
    }
  fread(config.buffer_c + sizeof (edcl_paquet_t), 1, file_size, fd);
  if (config.verbose)
    printf("File has been copied in memory.\n");

  if (config.big_endian)
    swap_bytes(file_size);

  /* Fill the edcl header */
  edcl_paquet			= config.buffer;
  edcl_paquet->operation	= WRITE_OP;
  edcl_paquet->length		= file_size;
  edcl_paquet->address		= config.memory_address;

  /* Send the file over the socket */
  if (send(config.socket, config.buffer, file_size, 0) == -1)
    goto error_send;
#ifdef __DEBUG
  write(1, config.buffer_c + sizeof (edcl_paquet_t), file_size);
#endif
  if (config.verbose)
    printf("File has been sent to the ethernet IP.\n");

  /* Release ressources */
  free(config.buffer);
  fclose(fd);

  return (0);

 error_send:
  free(config.buffer);
 error_malloc:
  fclose(fd);
 error_fopen:
  return (errno);
}
