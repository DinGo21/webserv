/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:46:54 by diego             #+#    #+#             */
/*   Updated: 2024/11/15 15:51:40 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Server.hpp"

Server::Server(): _routes(5), _routesCount(0), _maxSize(0) {}

Server::~Server() {}

size_t	Server::route_config_set(std::vector<std::string> &args, size_t i)
{
	if (!args[i].compare(0, 5, "root"))
	{
		return this->_routes[this->_routesCount].set_root(args, i);
	}
	if (!args[i].compare(0, 10, "autoindex"))
	{
		return this->_routes[this->_routesCount].set_autoindex(args, i);
	}
	if (!args[i].compare(0, 9, "methods"))
	{
		return this->_routes[this->_routesCount].set_methods(args, i);
	}
	if (!args[i].compare(0, 6, "index"))
	{
		return this->_routes[this->_routesCount].set_index(args, i);
	}
	if (!args[i].compare(0, 7, "return"))
	{
		return this->_routes[this->_routesCount].set_return(args, i);
	}
	if (!strchr("{};", args[i][0]))
	{
		std::cerr << "Unknown parameter: " << args[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	return i;
}

size_t	Server::route_config(const std::string &route, std::vector<std::string> &args, size_t i) 
{
	if (i + 1 < args.size() && !strchr("{", args[i + 1][0]))
	{
		std::cerr << "Expected a '{' after route keyword" << std::endl;
		exit(EXIT_FAILURE);
	}
	this->_routes.push_back(Route(this->_routesCount, route));
	i += 2;
	while (i < args.size() && !strchr("}", args[i][0]))
	{
		if (strchr("{", args[i][0]))
		{
			std::cerr << "Syntax error: {" << std::endl;
			exit(EXIT_FAILURE);
		}
		if (args[i][0] == ';')
			i++;
		i = this->route_config_set(args, i);
		i++;
	}
	std::cout << this->_routes[this->_routesCount];
	this->_routesCount++;
	return i;
}

std::string	Server::get_port() const
{
	return this->_port;
}

size_t	Server::set_port(const std::vector<std::string> &args, size_t i)
{
	size_t  j = 0;

	if (i + 1 < args.size() && strchr("{};", args[i + 1][0]))
	{
		std::cout << "Syntax error: " << args[i + 1] << std::endl;
		exit(EXIT_FAILURE);
	}
	i++;
	while (args[i][j] != '\0')
	{
		if (!isdigit(args[i][j++]))
		{
			exit(EXIT_FAILURE);
		}
	}
	this->_port = args[i];
	return i;
}

std::string	Server::get_host() const
{
	return this->_host;
}

size_t	Server::set_host(const std::vector<std::string> &args, size_t i)
{
	if (i + 1 < args.size() && strchr("{};", args[i + 1][0]))
	{
		std::cout << "Syntax error: " << args[i + 1] << std::endl;
		exit(EXIT_FAILURE);
	}
	this->_host = args[++i];
	return i;
}

size_t	Server::get_maxSize() const
{
	return this->_maxSize;
}

size_t    Server::set_maxSize(const std::vector<std::string> &args, size_t i)
{
	size_t  j = 0;

	if (i + 1 < args.size() && strchr("{};", args[i + 1][0]))
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
	this->_maxSize = atoi(args[++i].c_str());
	return i;
}

std::string Server::get_serverName() const
{
	return this->_serverName;
}

size_t    Server::set_serverName(const std::vector<std::string> &args, size_t i)
{
	if (i + 1 < args.size() && strchr("{};", args[i + 1][0]))
	{
		std::cout << "Syntax error: " << args[i + 1] << std::endl;
		exit(EXIT_FAILURE);
	}
	this->_serverName = args[++i];
	return i;
}

std::string Server::get_errorPage() const
{
	return this->_errorPage;
}

size_t	Server::set_errorPage(const std::vector<std::string> &args, size_t i)
{
	if (i + 1 < args.size() && args[i + 1].compare(0, 4, "404"))
	{
		std::cout << "Syntax error: " << args[i + 2] << std::endl;
		exit(EXIT_FAILURE);
	}
	i++;
	if (i + 1 < args.size() && strchr(";", args[i + 1][0]))
	{
		std::cout << "Syntax error: " << args[i + 1] << std::endl;
		exit(EXIT_FAILURE);
	}
	this->_errorPage = args[++i];
	return i;
}

std::string   Server::get_root() const
{
	return this->_root;
}

size_t	Server::set_root(const std::vector<std::string> &args, size_t i)
{
	if (i + 1 < args.size() && strchr(";{}", args[i + 1][0]))
	{
		std::cout << "Syntax error: " << args[i + 1] << std::endl;
		exit(EXIT_FAILURE);
	}
	this->_root = args[++i];
	return i;
}

std::ostream    &operator<<(std::ostream &o, const Server &rhs)
{
	o << "port: " << rhs.get_port() << '\n';
	o << "host: " << rhs.get_host() << '\n';
	o << "maxSize: " << rhs.get_maxSize() << '\n';
	o << "serverName: " << rhs.get_serverName() << '\n';
	o << "errorPage: " << rhs.get_errorPage() << '\n';
	o << "root: " << rhs.get_root() << std::endl;
	return o;
}
