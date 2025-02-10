/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:46:54 by diego             #+#    #+#             */
/*   Updated: 2025/02/06 08:17:21 by disantam         ###   ########.fr       */
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

uint	Server::get_nRoutes() const
{
	return (this->_nRoutes);
}

Route	&Server::get_route(const uint nRoute) const
{
	if (nRoute >= this->_nRoutes)
	{
		throw (Server::OutOfBoundsException());
	}
	return (this->_routes[nRoute]);
}

uint	Server::get_port() const
{
	return (this->_port);
}

const std::string	&Server::get_host() const
{
	return (this->_host);
}

const std::string	&Server::get_root() const
{
	return (this->_root);
}

const std::string	&Server::get_maxSize() const
{
	return (this->_maxSize);
}

const std::string	&Server::get_serverName() const
{
	return (this->_serverName);
}

const std::string	&Server::get_errorPage() const
{
	return (this->_errorPage);
}

void	Server::set_routes(Route* const routes, const uint nRoutes)
{
	this->_routes = routes;
	this->_nRoutes = nRoutes;
}

void	Server::set_port(const uint port)
{
	if (port > __UINT16_MAX__)
	{
		throw (Server::InvalidFormatException());
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

std::ostream	&operator<<(std::ostream &o, const Server &rhs)
{
	o << "server port: " << rhs.get_port() << '\n';
	o << "server host: " << rhs.get_host() << '\n';
	o << "server root: " << rhs.get_root() << '\n';
	o << "server max_size: " << rhs.get_maxSize() << '\n';
	o << "server server_name: " << rhs.get_serverName() << '\n';
	o << "server error_page: " << rhs.get_errorPage() << '\n';
	o << "server number of routes: " << rhs.get_nRoutes() << '\n';
	for (uint i = 0; i < rhs.get_nRoutes(); i++)
	{
		std::cout << rhs.get_route(i);
	}
	return (o);
}
