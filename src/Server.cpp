/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:46:54 by diego             #+#    #+#             */
/*   Updated: 2025/01/17 11:27:06 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Server.hpp"

uint	Server::_nServers = 0;

uint	Server::get_nServers()
{
	return Server::_nServers;
}

Server::Server(): _nRoutes(), _routes(NULL), _port(), _host(), _root(), _maxSize(), _serverName(), _errorPage() 
{
	Server::_nServers++;
}

Server::~Server()
{
	delete [] this->_routes;
}

const char	*Server::InvalidFormatException::what() const throw()
{
	return "Invalid value format";
}

const char	*Server::OutOfBoundsException::what() const throw()
{
	return "Trying to access out of bounds";
}

Route	&Server::get_route(const uint nRoute) const
{
	if (nRoute >= this->_nRoutes)
	{
		throw (Server::OutOfBoundsException());
	}
	return (this->_routes[nRoute]);
}

void	Server::set_routes(Route* const routes, const uint nRoutes)
{
	this->_routes = routes;
	this->_nRoutes = nRoutes;
}

void	Server::set_port(const std::string &port)
{
	uint	i = 0;

	while (port[i] != '\0')
	{
		if (!isdigit(port[i]))
			throw (Server::InvalidFormatException());
		i++;
	}
	this->_port = port;
}

void	Server::set_host(const std::string &host)
{
	this->_host = host;
}

void	Server::set_root(const std::string &root)
{
	this->_root = root;
}

void	Server::set_maxSize(const std::string &maxSize)
{
	uint	i = 0;

	while (maxSize[i] != '\0')
	{
		if (!isdigit(maxSize[i]))
			throw (Server::InvalidFormatException());
		i++;
	}
	this->_maxSize = maxSize;
}

void	Server::set_serverName(const std::string &serverName)
{
	this->_serverName = serverName;
}

void	Server::set_errorPage(const std::string &errorPage)
{
	this->_errorPage = errorPage;
}