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

#ifndef GRETH_H_
# define GRETH_H_

# include <unistd.h>
# include <stdlib.h>

# include <stdio.h>
# include <getopt.h>
# include <string.h>

# include <errno.h>

# include "connect.h"
# include "edcl_protocol.h"

# define true			1
# define false			0

# define HOSTNAME_MAX_LENGTH	20
# define FILENAME_MAX_LENGTH	32

# define BANNER					\
  "/**\n"					\
  " * greth - read/write dram memory\n"		\
  " * \t by Quentin Casasnovas\n"		\
  " */\n\n"

typedef struct		greth_conf_t
{
  int			socket;
  char			ip[HOSTNAME_MAX_LENGTH];
  char			filename[FILENAME_MAX_LENGTH];
  char			verbose;
  char			big_endian;
  unsigned long		memory_address;
  union 
  {
    void*		buffer;
    edcl_paquet_t*	paquet;
  };
} greth_conf_t;

extern greth_conf_t config;

#endif /* !GRETH_H_ */
