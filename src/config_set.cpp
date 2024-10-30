/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_set.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:30:01 by diego             #+#    #+#             */
/*   Updated: 2024/10/30 11:35:09 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

uint	server_config_set_port(Server &server, std::vector<std::string> &args, size_t i)
{
	size_t  j = 0;

	if (i + 1 < args.size() && strchr(";{}", args[i + 1][0]))
	{
		std::cout << "Syntax error: " << args[i + 1] << std::endl;
		exit(EXIT_FAILURE);
	}
	while (args[i + 1][j] != '\0')
	{
		if (!isdigit(args[i + 1][j++]))
		{
			exit(EXIT_FAILURE);
		}
	}
	if (i + 2 < args.size() && !strchr(";{}", args[i + 2][0]))
	{
		std::cout << "Syntax error: " << args[i + 2] << std::endl;
		exit(EXIT_FAILURE);
	}
	server.set_port(atoi(args[i + 2].c_str()));
	return 1;
}

uint	server_config_set_serverName(Server &server, std::vector<std::string> &args, size_t i)
{
	if (i + 1 < args.size() && strchr(";{}", args[i + 1][0]))
	{
		std::cout << "Syntax error: " << args[i + 1] << std::endl;
		exit(EXIT_FAILURE);
	}
	if (i + 2 < args.size() && !strchr(";{}", args[i + 2][0]))
	{
		std::cout << "Syntax error: " << args[i + 2] << std::endl;
		exit(EXIT_FAILURE);
	}
	server.set_serverName(args[i + 1]);
	return 1;
}

uint	server_config_set_host(Server &server, std::vector<std::string> &args, size_t i)
{
	if (i + 1 < args.size() && strchr(";{}", args[i + 1][0]))
	{
		std::cout << "Syntax error: " << args[i + 1] << std::endl;
		exit(EXIT_FAILURE);
	}
	if (i + 2 < args.size() && !strchr(";{}", args[i + 2][0]))
	{
		std::cout << "Syntax error: " << args[i + 2] << std::endl;
		exit(EXIT_FAILURE);
	}
	server.set_host(args[i + 1]);
	return 1;
}

uint	server_config_set_errorPage(Server &server, std::vector<std::string> &args, size_t i)
{
	if (i + 1 < args.size() && strchr(";{}", args[i + 1][0]))
	{
		std::cout << "Syntax error: " << args[i + 1] << std::endl;
		exit(EXIT_FAILURE);
	}
	if (args[i + 1].compare(0, 4, "404") || strchr(";{}", args[i + 2][0]))
	{
		std::cout << "Syntax error: " << args[i + 2] << std::endl;
		exit(EXIT_FAILURE);
	}
	if (i + 3 < args.size() && !strchr(";{}", args[i + 3][0]))
	{
		std::cout << "Syntax error: " << args[i + 3] << std::endl;
		exit(EXIT_FAILURE);
	}
	server.set_errorPage(args[i + 2]);
	return 2;
}

uint	server_config_set_maxSize(Server &server, std::vector<std::string> &args, size_t i)
{
	size_t  j = 0;

	if (i + 1 < args.size() && strchr(";{}", args[i + 1][0]))
	{
		std::cout << "Syntax error: " << args[i + 1] << std::endl;
		exit(EXIT_FAILURE);
	}
	while (args[i + 1][j] != '\0')
	{
		if (!isdigit(args[i + 1][j++]))
		{
			exit(EXIT_FAILURE);
		}
	}
	if (i + 2 < args.size() && !strchr(";{}", args[i + 2][0]))
	{
		std::cout << "Syntax error: " << args[i + 2] << std::endl;
		exit(EXIT_FAILURE);
	}
	server.set_maxSize(atoi(args[i + 1].c_str()));
	return 1;
}

uint	server_config_set_root(Server &server, std::vector<std::string> &args, size_t i)
{
	if (i + 1 < args.size() && strchr(";{}", args[i + 1][0]))
	{
		std::cout << "Syntax error: " << args[i + 1] << std::endl;
		exit(EXIT_FAILURE);
	}
	if (i + 2 < args.size() && !strchr(";{}", args[i + 2][0]))
	{
		std::cout << "Syntax error: " << args[i + 2] << std::endl;
		exit(EXIT_FAILURE);
	}
	server.set_root(args[i + 1]);
	return 1;
}
