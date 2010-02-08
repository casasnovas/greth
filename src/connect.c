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
int			create_connection(void)
{
  struct addrinfo       hints;
  struct addrinfo*      serv_info;

  memset(&hints, 0, sizeof (struct addrinfo));

  /* It's a UDP connection */
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  
  getaddrinfo(config.ip, "41491", &hints, &serv_info);

  /* Open the socket */
  if ((config.socket = socket(serv_info->ai_family, 
			      serv_info->ai_socktype, 
			      serv_info->ai_protocol)) == -1)
    goto error_socket;

  /* Initiate the connection */
  if (connect(config.socket, serv_info->ai_addr, serv_info->ai_addrlen) == -1)
    goto error_connect;

  freeaddrinfo(serv_info);

  if (config.verbose)
    printf("Connection to the ethernet IP opened.\n");

  return (0);

 error_connect:
  close(config.socket);
 error_socket:
  if (config.verbose)
    printf("Error while trying to connect to the ethernet IP.\n");

  return (errno);
}

/**
 * Properly close the connection initiated to the ethernet IP and set the
 * corresponding field in the config structure to -1.
 */
void		close_connection(void)
{
  if (config.verbose)
    printf("Connection closed.\n");

  close(config.socket);
}

