/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:56:34 by disantam          #+#    #+#             */
/*   Updated: 2025/02/14 13:16:26 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void	run_server(Server *server)
{
	socket_t	data;

	server->init(data);
	if (server->set_dir() < 0 || server->socket_create(data) < 0 ||
		server->run(data) < 0)
	{
		delete [] server;
		exit(EXIT_FAILURE);
	}
}

Server	*run_config(const char *path)
{
	Config	config;

	if (config.set_file(path) < 0)
	{
		return (NULL);
	}
	config.read_file();
	if (config.init() < 0 || config.parse() < 0)
	{
		delete [] config.servers;
		return (NULL);
	}
	return config.servers;
}

int	main(int argc, char *argv[])
{
	Server	*servers;

	if (argc != 2)
	{
		std::cerr << "No arguments passed, using default configuration file" << std::endl;
		return 1;
	}
	servers = run_config(argv[1]);
	run_server(servers);
	delete [] servers;
	return 0;
}
