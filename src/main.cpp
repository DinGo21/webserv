/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:56:34 by disantam          #+#    #+#             */
/*   Updated: 2025/01/21 16:23:35 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

Server	*config_server(const char *path)
{
	Config	config;

	if (config.set_file(path) < 0)
	{
		return (NULL);
	}
	config.read_file();
	if (config.init() < 0)
	{
		delete [] config.servers;
		return (NULL);
	}
	if (config.parse() < 0)
	{
		delete [] config.servers;
		return (NULL);
	}
	return config.servers;
}

void	init_connection(Server *servers)
{
	int					server_fd = socket(AF_INET, SOCK_STREAM, 0);
	int					nb = 0;
	int					new_socket = 0;
	struct sockaddr_in	addr;
	uint				addrlen = sizeof(addr);
	uint				port = 8080;
	char				buff[3001];
	char				hello[] = "hello from my webserver!\n";

	(void)servers;
	memset((void *)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	if (server_fd < 0)
	{
		std::cerr << "Cannot create socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		std::cerr << "Bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		std::cerr << "Failed to listen for connections" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (true)
	{
		new_socket = accept(server_fd, (struct sockaddr *)&addr, (socklen_t *)&addrlen);
		if (new_socket < 0)
		{
			std::cerr << "Failed to accept connection" << std::endl;
			exit(EXIT_FAILURE);        
		}
		nb = read(new_socket, buff, 3000);
		buff[nb] = '\0';
		std::cout << buff;
		write(new_socket, hello, strlen(hello));
		close(new_socket);
	}
}

int	main(int argc, char *argv[])
{
	Server	*servers;

	if (argc != 2)
	{
		std::cerr << "No arguments passed, using default configuration file" << std::endl;
		return 1;
	}
	servers = config_server(argv[1]);
	init_connection(servers);
	delete [] servers;
	return 0;
}
