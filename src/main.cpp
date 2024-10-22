/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:56:34 by disantam          #+#    #+#             */
/*   Updated: 2024/10/22 15:23:25 by diego            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

uint	server_config_set(Server &server, std::vector<std::string> &args, size_t i)
{
	uint	j = 0;

	if (!args[i].compare(0, 7, "listen"))
	{
		if (i + 1 < args.size() && !strchr(";{}", args[i + 1][0]))
			exit(EXIT_FAILURE);
		while (args[i + 1][j] != '\0')
		{
			if (!isdigit(args[i][j++]))
				exit(EXIT_FAILURE);
		}
		server.set_port(atoi(args[i + 1].c_str()));
		return 1;
	}
	if (!args[i].compare(0, 6, "host"))
	{
		if (i + 1 < args.size() && !strchr(";{}", args[i + 1][0]))
			exit(EXIT_FAILURE);
		server.set_host(args[i + 1]);
		return 1;
	}
	if (!args[i].compare(0, 12, "server_name"))
	{
		if (i + 1 < args.size() && !strchr(";{}", args[i + 1][0]))
			exit(EXIT_FAILURE);
		server.set_serverName(args[i + 1]);
		return 1;
	}
	if (!args[i].compare(0, 11, "error_page"))
	{
		if (i + 1 < args.size() && !strchr(";{}", args[i + 1][0]))
			exit(EXIT_FAILURE);
		if (args[i + 1].compare(0, 4, "404") || !strchr(";{}", args[i + 2][0]))
			exit(EXIT_FAILURE);
		server.set_errorPage(args[i + 2]);
		return 2;
	}
	if (!args[i].compare(0, 21, "client_max_body_size"))
	{
		if (i + 1 < args.size() && !strchr(";{}", args[i + 1][0]))
			exit(EXIT_FAILURE);
		while (args[i + 1][j] != '\0')
		{
			if (!isdigit(args[i][j++]))
				exit(EXIT_FAILURE);
		}
		server.set_maxSize(atoi(args[i + 1].c_str()));
		return 1;
	}
	if (!args[i + 1].compare(0, 5, "root"))
	{
		if (i + 1 < args.size() && !strchr(";{}", args[i + 1][0]))
			exit(EXIT_FAILURE);
		server.set_root(args[i + 1]);
		return 1;
	}
	return 0;
}

void	server_config_parse(Server &server, std::vector<std::string> &args)
{
	size_t		i = 0;
	uint		f = 0;

	while (i < args.size())
	{
		if (!args[i].compare("server") && !args[i].compare("{") && f != 1)
			f = 1;
		if (!args[i].compare("}") && f != 0)
			f = 0;
		if (f)	
			i += server_config_set(server, args, i);
		i++;
	}
}

//TODO: handle comments
std::vector<std::string>	server_config_get(std::ifstream &config)
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
	for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	return args;
}

int	main(int argc, char *argv[])
{
	Server						server;
	std::ifstream				config;
	std::vector<std::string>	args;

	if (argc != 2)
	{
		std::cerr << "Server requires configuration file" << std::endl;
		return 1;
	}
	config.open(argv[1]);
	if (!config.is_open())
	{
		std::cerr << "Unable to open file: " << argv[1] << std::endl;
		return 1;
	}
	args = server_config_get(config);
	server_config_parse(server, args);
	config.close();
	return 0;
}
