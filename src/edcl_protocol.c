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

  for (i = 0; i < ((filesize) / 4); ++i)
    buffer_i[i] = to_big_endian_32(buffer_i[i]);
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
  if (config.verbose)
    printf("File size is: %dKo.\n", file_size);

  /* Copy the file in memory */
  if ((config.buffer = calloc(1, file_size + sizeof (edcl_paquet_t))) == NULL)
    {
      printf("Error allocating memory.\n");
      goto error_malloc;
    }
  fread(config.buffer_c + sizeof (edcl_paquet_t), 1, file_size, fd);
  if (config.verbose)
    printf("File has been copied in memory.\n");

  /* Fill the edcl header */
  edcl_paquet			= config.buffer;
  edcl_paquet->offset		= 0x1234;
  set_operation(edcl_paquet->layer_field, WRITE_OP);
  set_length(edcl_paquet->layer_field, file_size);
  edcl_paquet->address		= config.memory_address;

  /* Swap bytes to big endian if the flag is active */
  if (config.big_endian)
    swap_bytes(file_size);

  /* Send the file over the socket */
  if (send(config.socket,
	   config.buffer,
	   file_size + sizeof (edcl_paquet_t),
	   0) == -1)
    goto error_send;

#ifdef __DEBUG
  printf("0x%08x\t0x%08x\t0x%08x.\n",
	 config.buffer_i[0],
	 *(config.buffer_i + 1),
	 *(config.buffer_i + 2));
  /* write(1, config.buffer_c + sizeof (edcl_paquet_t), file_size); */
#endif

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
