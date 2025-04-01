/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:56:34 by disantam          #+#    #+#             */
/*   Updated: 2025/03/31 12:37:07 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	run_config(const char *path, Server **servers)
{
	Config	config;

	if (config.set_file(path) < 0)
	{
		return (-1);
	}
	config.read_file();
	if (config.init() < 0 || config.parse() < 0 || config.check() < 0)
	{
		return (-1);
	}
	for (uint i = 0; i < Server::get_nServers(); i++)
	{
		std::cout << config.servers[i] << std::endl;
	}
	*servers = config.servers;
	return 0;
}

int	run_monitor(Server *servers)
{
	Monitor	monitor(servers);

	if (monitor.sockets_init() < 0)
	{
		return (-1);
	}
	if (monitor.run() < 0)
	{
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	Server	*servers = NULL;

	if (argc != 2)
	{
		std::cerr << "Server requires configuration file" << std::endl;
		return 1;
	}
	run_config(argv[1], &servers);
	run_monitor(servers);
	delete [] servers;
	return (0);
}
