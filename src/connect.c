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

#include "connect.h"

/**
 * Initiate a connection to the ethernet IP and update the corresponding field
 * in the config structure.
 *
 * Returns 0 on success, the error value otherwize.
 */
int			create_connections(void)
{
	unsigned short int	source_port;
	struct addrinfo       hints;

	/* It's a UDP connection */
	memset(&hints, 0, sizeof (struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	getaddrinfo(config.ip, "4242", &hints, &(config.serv_info));

	/* Create the socket */
	if ((config.socket = socket(config.serv_info->ai_family,
				    config.serv_info->ai_socktype,
				    config.serv_info->ai_protocol)) == -1)
		goto error_socket;

	if (config.verbose)
		fprintf(stderr,
			"Connection to the ethernet IP opened.\n");

	return (0);

 error_connect:
	close(config.socket);
 error_socket:
	if (config.verbose)
		fprintf(stderr,
			"Error while trying to connect to the ethernet IP.\n");
	return (errno);
}

/**
 * Properly close the connection initiated to the ethernet IP and set the
 * corresponding field in the config structure to -1.
 */
void		close_connections(void)
{
	if (config.verbose)
		fprintf(stderr,
			"Connection closed.\n");

	freeaddrinfo(config.serv_info);

	close(config.socket);
}

