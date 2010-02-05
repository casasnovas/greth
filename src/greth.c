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

#include "greth.h"

static void	print_usage(void)
{
  printf("Usage: ...\n");
}

static struct option l_opts[] =
  {
    {"ip",		required_argument,	0, 'i'},
    {"help",		no_argument,		0, 'h'},
    {"verbose",		no_argument,		0, 'v'},
    {"big-endian",	no_argument,		0, 'g'},
    {"memory-address",	no_argument,		0, 'm'},
    {0,			0,			0,  0 }
  };

greth_conf_t	config;

/**
 * Retreive options given by the command line arguments and set the fields of
 * the config structure accordingly.
 *
 * Returns 0 upon success, and exits when an unknown option is given.
 */
static int	treat_options(int argc, char** argv)
{
  int		option = 0;

  memset(&config, 0x0, sizeof (greth_conf_t));

  while ((option = getopt_long(argc, argv, "ghi:mv", l_opts, NULL)) != EOF)
    {
      switch (option)
	{
	case 'i':
	  strncpy(config.ip, optarg, HOSTNAME_MAX_LENGTH);
	  break;
	case 'g':
	  config.big_endian = true;
	  break;
	case 'h':
	  print_usage();
	  exit (0);
	  break;
	case 'm':
	  config.memory_address = strtoul(optarg, NULL, 0);
	  config.memory_address &= ~3;
	  break;
	case 'v':
	  config.verbose = true;
	  break;
	default:
	  print_usage();
	  return (1);
	  break;
	}
    } /* getopt_long(...) != EOF */

  if (config.verbose)
    printf(BANNER
	   "Configuration :\n"
	   "\t IP:\t\t %s\n"
	   "\t Address:\t 0x%08x\n"
	   "\t Verbose:\t %d\n"
	   "\t Big endian:\t %d\n\n",
	   config.ip, config.memory_address, 
	   config.verbose, config.big_endian);
    
  return (0);
}

int		main(int argc, char** argv)
{
  int		err_num;

  if ((err_num = treat_options(argc, argv)) != 0)
    goto error;

  if ((err_num = create_connection()) != 0)
    goto error;

  close_connection();
  
  return (0);

 error:
  return (err_num);
}
