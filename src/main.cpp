/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:56:34 by disantam          #+#    #+#             */
/*   Updated: 2025/01/16 15:02:10 by disantam         ###   ########.fr       */
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
		return (NULL);
	}
	if (config.parse() < 0)
	{
		return (NULL);
	}
	return NULL;
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
	(void)servers;
	return 0;
}
