/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:29:21 by disantam          #+#    #+#             */
/*   Updated: 2024/11/15 15:48:51 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

static uint	server_config_set(Server &server, std::vector<std::string> &args, size_t i)
{
	if (!args[i].compare(0, 7, "listen"))
	{
		return server.set_port(args, i);
	}
	if (!args[i].compare(0, 6, "host"))
	{
		return server.set_host(args, i);
	}
	if (!args[i].compare(0, 12, "server_name"))
	{
		return server.set_serverName(args, i);
	}
	if (!args[i].compare(0, 11, "error_page"))
	{
		return server.set_errorPage(args, i);
	}
	if (!args[i].compare(0, 21, "client_max_body_size"))
	{
		return server.set_maxSize(args, i);
	}
	if (!args[i].compare(0, 5, "root"))
	{
		return server.set_root(args, i);
	}
	if (args[i].compare(0, 6, "route") && !strchr("{};", args[i][0]))
	{
		std::cerr << "Unknown parameter: " << args[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	return i;
}

static void	server_config_parse(Server &server, std::vector<std::string> &args)
{
	size_t	i = 0;

	while (i < args.size() && args[i].compare(0, 7, "server"))
		i++;
	if (i + 1 < args.size() && args[i + 1][0] != '{')
	{
		std::cerr << "Expected a '{' after server keyword" << std::endl;
		exit(EXIT_FAILURE);
	}
	i += 2;
	while (i < args.size() && args[i][0] != '}')
	{
		if (strchr("{", args[i][0]))
		{
			std::cerr << "Syntax error: {" << std::endl;
			exit(EXIT_FAILURE);
		}
		if (args[i][0] == ';')
			i++;
		if (i < args.size())
			i = server_config_set(server, args, i);
		if (i + 1 < args.size() && !args[i].compare("route") && !strchr("{};", args[i + 1][0]))
		{
			i++;
			server.route_config(args[i], args, i);
		}
		i++;
	}
	std::cout << server;
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
}
