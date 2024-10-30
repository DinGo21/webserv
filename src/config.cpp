/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:29:21 by disantam          #+#    #+#             */
/*   Updated: 2024/10/30 11:37:57 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

static uint	server_config_set(Server &server, std::vector<std::string> &args, size_t i)
{
	if (!args[i].compare(0, 7, "listen"))
	{
		return server_config_set_port(server, args, i);
	}
	if (!args[i].compare(0, 6, "host"))
	{
		return server_config_set_host(server, args , i);
	}
	if (!args[i].compare(0, 12, "server_name"))
	{
		return server_config_set_serverName(server, args, i);
	}
	if (!args[i].compare(0, 11, "error_page"))
	{
		return server_config_set_errorPage(server, args, i);
	}
	if (!args[i].compare(0, 21, "client_max_body_size"))
	{
		return server_config_set_maxSize(server, args, i);
	}
	if (!args[i].compare(0, 5, "root"))
	{
		return server_config_set_root(server, args, i);
	}
	return 0;
}

//TODO: Handle multiple server contexts
static void	server_config_parse(Server &server, std::vector<std::string> &args)
{
	size_t	i = 0;
	uint	c = 0;
	uint	f = 0;

	while (i < args.size())
	{
		if (!args[i].compare("server") && !args[i + 1].compare("{") && f != 1)
			f = 1;
		if (!args[i].compare("}") && f != 0)
			f = 0;
			
		if (f)
			i += server_config_set(server, args, i);
		
		i++;
	}
}

//TODO: handle comments
static std::vector<std::string>	server_config_get(std::ifstream &config)
{
	size_t						i = 0;
	size_t						j = 0;
	std::string					tmp;
	std::string					raw;
	std::vector<std::string>	args;

	while (std::getline(config, tmp))
	{
		raw += tmp;
		raw.push_back('\n');
	}
	while (raw[i] != '\0')
	{
		while (strchr(" \t\n", raw[i]) && raw[i] != '\0')
			i++;
		if (raw[i] == '\0')
			break ;
		j = raw.find_first_of(" {};\t\n", i);
		if (i - j)
			args.push_back(raw.substr(i, j - i));
		i = j;
		if (strchr(";{}", raw[i]))
		{
			args.push_back(raw.substr(i, 1));
			i++;
		}
	}
	return args;
}

void	server_config(Server &server, char *path)
{
	std::ifstream				config;
	std::vector<std::string>	args;

	config.open(path);
	if (!config.is_open())
	{
		std::cerr << "Unable to open file: " << path << std::endl;
		exit(EXIT_FAILURE);
	}
	args = server_config_get(config);
	for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	server_config_parse(server, args);
	config.close();
	std::cout << server;
}
