/*  ABCDEFGHIJKL
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

#ifndef EDCL_PROTOCOL_H_
# define EDCL_PROTOCOL_H_

# include "greth.h"

# define READ_OP	0
# define WRITE_OP	1

# define get_file_size(File_size, Fd)		\
  fseek((Fd), 0, SEEK_END);			\
  (File_size) = ftell((Fd));			\
  rewind((Fd));

# define to_big_endian(Nb)			\
  ((((Nb) & 0xff) << 24)	|		\
   (((Nb) & 0xff00) << 8)	|		\
   (((Nb) & 0xff0000) >> 8)	|		\
   (((Nb) & 0xff000000) >> 24))


typedef struct	edcl_paquet_t
{
  unsigned int	offset:16;	/* Needed to align to word boundaries */
  unsigned int	sequence:14;
  unsigned int	operation:1;	/* READ_OP || WRITE_OP */
  unsigned int	length:10;	/* Size of the datas */
  unsigned int	unused:7;	/* Unused bits to align */
  unsigned int	address:32;	/* Address in memory to read/write to/from */
} __attribute__ ((packed)) edcl_paquet_t;

int		send_file(void);

#endif /* !EDCL_PROTOCOL_H_ */
