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
# define FILENAME_MAX_LENGTH	64
# define BANNER					\
  "/**\n"					\
  " * greth - read/write from/to ahb bus\n"	\
  " * \t by Quentin Casasnovas\n"		\
  " */\n\n"

# define WRITE_ACTION		1
# define READ_ACTION		2

/*
 * Arch not specific macros function
 */

# define min(A, B)	((A) < (B) ? (A) : (B))
# define max(A, B)	((A) > (B) ? (A) : (B))

/*
 * Types
 */

typedef struct		greth_conf_t
{
  int			socket;
  char			ip[HOSTNAME_MAX_LENGTH];
  char			filename[FILENAME_MAX_LENGTH];
  char			action;
  char			verbose;
  char			big_endian;
  unsigned int		memory_address;
  unsigned int		data_size;
  unsigned int		word;
  struct addrinfo*	serv_info;
  union
  {
    unsigned int*		data;
    unsigned char*		data_c;
  };
} greth_conf_t;

extern greth_conf_t config;

#endif /* !GRETH_H_ */
