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
  (File_size) = (unsigned int) ftell((Fd));	\
  rewind((Fd));

# define set_operation(Layer_Field, Operation)	\
  (Layer_Field) |= ((Operation & 0x1) << 9);

# define set_length(Layer_Field, File_Size)		\
  (Layer_Field) |=					\
    (((File_Size) & 0x001) >> 0 << 31)	|		\
    (((File_Size) & 0x0fe) >> 1 << 16)	|		\
    (((File_Size) & 0x200) >> 9 << 8) ;

# define to_big_endian_16(Nb)			\
  ((((Nb) & 0xff) << 8)	| (((Nb) & 0xff00) >> 8))

# define to_big_endian_32(Nb)			\
  ((((Nb) & 0xff) << 24)	|		\
   (((Nb) & 0xff00) << 8)	|		\
   (((Nb) & 0xff0000) >> 8)	|		\
   (((Nb) & 0xff000000) >> 24))

typedef struct		edcl_paquet_t
{
  unsigned short	offset;		/* Needed to align to word boundaries */
  unsigned int		layer_field;
  unsigned int		address;	/* Address in memory to read/write to/from */
} __attribute__ ((packed)) edcl_paquet_t;

int		send_file(void);

#endif /* !EDCL_PROTOCOL_H_ */
