/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:46:54 by diego             #+#    #+#             */
/*   Updated: 2025/02/26 12:14:43 by disantam         ###   ########.fr       */
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

int	Server::run(socket_t &data)
{
	FD_ZERO(&data.masterSet);
	FD_SET(data.serverSock, &data.masterSet);
	while (true)
	{
		memcpy(&data.workingSet, &data.masterSet, sizeof(data.masterSet));
		data.timeout.tv_sec = 1 * 60;
		data.timeout.tv_usec = 0;
		data.ready = select(data.maxSock + 1, &data.workingSet, NULL, NULL, &data.timeout);
		if (data.ready < 0)
		{
			std::cerr << strerror(errno) << std::endl;
			return (-1);
		}
		if (data.ready == 0)
			break;
		if (this->register_event(data) < 0)
			break;
	}
	for (int i = 0; i < data.maxSock; i++)
	{
		if (FD_ISSET(i, &data.masterSet))
			close(i);
	}
	return (0);
}

int	Server::set_dir()
{
	char	buf[500];

	if (chdir(this->_root.c_str()) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	std::cout << getcwd(buf, 500) << std::endl;
	return (0);
}

void	Server::init(socket_t &sockData)
{
	memset(&sockData, 0, sizeof(sockData));
	sockData.addr.sin_family = AF_INET;
	sockData.addr.sin_port = htons(this->_port);
	sockData.addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockData.addrlen = sizeof(sockData.addr);
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
