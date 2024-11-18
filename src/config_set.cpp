/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_set.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:40:03 by disantam          #+#    #+#             */
/*   Updated: 2024/11/18 16:22:31 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

size_t	server_config_set_port(Server &server, const std::vector<std::string> &args, size_t i)
{
	i++;
	if (strchr("{};", args[i][0]))
	{
		std::cerr << "Syntax error: " << args[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	try
	{
		server.set_port(args[i]);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	return i;
}

size_t	server_config_set_host(Server &server, const std::vector<std::string> &args, size_t i)
{
	i++;
	if (strchr("{};", args[i][0]))
	{
		std::cout << "Syntax error: " << args[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	server.set_host(args[i]);
	return i;
}

size_t	server_config_set_root(Server &server, const std::vector<std::string> &args, size_t i)
{
	i++;
	if (strchr(";{}", args[i][0]))
	{
		std::cout << "Syntax error: " << args[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	server.set_root(args[i]);
	return i;
}

size_t	server_config_set_maxSize(Server &server, const std::vector<std::string> &args, size_t i)
{
	i++;
	if (strchr("{};", args[i][0]))
	{
		std::cout << "Syntax error: " << args[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	try
	{
		server.set_maxSize(args[i]);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	return i;
}

size_t	server_config_set_errorPage(Server &server, const std::vector<std::string> &args, size_t i)
{
	i++;
	if (args[i].compare(0, 4, "404"))
	{
		std::cout << "Syntax error: " << args[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	i++;
	if (args[i][0] == ';')
	{
		std::cout << "Syntax error: " << args[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	server.set_errorPage(args[i]);
	return i;
}

size_t	server_config_set_serverName(Server &server, const std::vector<std::string> &args, size_t i)
{
	i++;
	if (strchr("{};", args[i][0]))
	{
		std::cout << "Syntax error: " << args[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	server.set_serverName(args[i]);
	return i;
}
