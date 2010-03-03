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

/**
 * Prints usage information in case a bad argument has been given or the flag
 * --help is active.
 */
static void	print_usage(const char*	binary_name)
{
	fprintf(stderr,
		"Usage: "
		"\t%s read --ip/-i ip_address "
		"\n\t\t [--memory-address/-m memory_address] (default to 0x40000000)"
		"\n\t\t [--length/-l length] (default to 4)"
		"\n\t\t [--big-endian/-b] "
		"\n\t\t [--verbose/-v]\n"
		"or: "
		"\t%s write --ip/-i ip_address "
		"\n\t\t [--memory-address/-m memory_address] (default to 0x40000000)"
		"\n\t\t [[--file/-f filename]/[--word/-w word_value]] (default to -w 0x1234CAFE)"
		"\n\t\t [--check-copy/-c] (not implemented yet)"
		"\n\t\t [--big-endian/-b] "
		"\n\t\t [--verbose/-v]\n"
		"or: "
		"\t%s run [--run-address/-r memory_address] (default to 0x00)"
		"\n\t\t --ip/-i ip_address\n"
		"or: "
		"\t%s continue --ip/-i ip_address\n"
		"or: "
		"\t%s halt --ip/-i ip_address\n"
		"or: "
		"\t%s help\n",
		binary_name, binary_name, binary_name,
		binary_name, binary_name, binary_name);
}

/**
 * Check that all parameters are well known.
 */
static int	check_config(void)
{
	/* Check the ip is present */
	if (config.ip[0] == 0)
		return (1);

	/* Check the memory address */
	if (config.memory_address == 0)
		config.memory_address = 0x40000000;

	if (config.action == WRITE_ACTION) {
		/* No filename and no word, default to word 0x1234CAFE */
		if (config.filename[0] == 0 && config.word == 0)
			config.word = 0x1234CAFE;
		/* A filename AND a word at the same time, error */
		else if (config.filename[0] != 0 && config.word != 0)
			return (1);
	}
	else if (config.action == READ_ACTION) {
		/* No length, default to 4 */
		if (config.data_size == 0)
			config.data_size = 4;
	}
	else if (config.action == RUN_ACTION) {
	}
	else
		/* No action is specified */
		return (1);

	return (0);
}

static struct option l_opts[] =	{
	{"ip",			required_argument,	0, 'i'},
	{"file",		required_argument,	0, 'f'},
	{"word",		required_argument,	0, 'w'},
	{"help",		no_argument,		0, 'h'},
	{"length",		required_argument,	0, 'l'},
	{"verbose",		no_argument,		0, 'v'},
	{"big-endian",		no_argument,		0, 'b'},
	{"check-copy",		no_argument,		0, 'c'},
	{"run-address",		required_argument,	0, 'r'},
	{"memory-address",	required_argument,	0, 'm'},
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

	/* Clear the configuration structure */
	memset(&config, 0x0, sizeof (greth_conf_t));

	/* Retreive the action to perform and inc argv to be able to parse options */
	if (argc <= 1) {
		print_usage(argv[0]);
		return (1);
	}
	if (strncmp(argv[1], "write", 5) == 0) {
		config.action = WRITE_ACTION;
		++argv;
		--argc;
	}
	else if (strncmp(argv[1], "read", 4) == 0) {
		config.action = READ_ACTION;
		++argv;
		--argc;
	}
	else if (strncmp(argv[1], "run", 12) == 0) {
		config.action = RUN_ACTION;
		++argv;
		--argc;
	}

	/* Parse the command line options in case of a write or read action */
	while ((option = getopt_long(argc, argv, "f:bhi:l:m:r:vw:", l_opts, NULL)) != EOF) {
		switch (option)	{
		case 'f':
			strncpy(config.filename, optarg, FILENAME_MAX_LENGTH);
			break;
		case 'b':
			config.big_endian = true;
			break;
		case 'c':
			break;
		case 'h':
			print_usage(argv[0]);
			exit (0);
			break;
		case 'i':
			strncpy(config.ip, optarg, HOSTNAME_MAX_LENGTH);
			break;
		case 'l':
			config.data_size = strtoul(optarg, NULL, 0);
			break;
		case 'm':
			config.memory_address = strtoul(optarg, NULL, 0);
			config.memory_address &= ~3;
			break;
		case 'r':
			config.run_address = strtoul(optarg, NULL, 0);
			config.run_address &= ~3;
			break;
		case 'v':
			config.verbose = true;
			break;
		case 'w':
			config.word = strtoul(optarg, NULL, 0);
			break;
		default:
			goto error_args;
			break;
		}
	} /* getopt_long() != EOF */

	/* Check that we have what we need */
	if (check_config() != 0)
		goto error_args;

	if (config.verbose)
		fprintf(stderr,
			BANNER
			"Configuration :\n"
			"\t IP:\t\t %s\n"
			"\t Address:\t 0x%08x\n"
			"\t Verbose:\t %d\n"
			"\t Big endian:\t %d\n\n",
			config.ip, config.memory_address,
			config.verbose, config.big_endian);

	return (0);

 error_args:
	print_usage(argv[0]);
	return (-1);
}

int		main(int argc, char** argv)
{
	int		err_num;

	/* Parse command line arguments */
	if ((err_num = treat_options(argc, argv)) != 0)
		goto error;

	/* Open the socket to the ethernet IP */
	if ((err_num = create_connections()) != 0)
		goto error;

	if (config.action == WRITE_ACTION) {
		if (config.filename[0] != 0) {
			if ((err_num = send_file()) != 0)
				goto error;
		}
		else {
			if ((err_num = send_word()) != 0)
				goto error;
		}
	}
	else if (config.action == RUN_ACTION) {
		if ((err_num = run_address()) !=0)
			goto error;
	}

	/* Close the socket to the ethernet IP */
	close_connections();

	return (0);

 error:
	return (err_num);
}
