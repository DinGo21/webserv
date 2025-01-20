/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:56:34 by disantam          #+#    #+#             */
/*   Updated: 2025/01/20 11:47:07 by disantam         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	Server	*servers;

	if (argc != 2)
	{
		std::cerr << "No arguments passed, using default configuration file" << std::endl;
		return 1;
	}
	servers = config_server(argv[1]);
	delete [] servers;
	return 0;
}
