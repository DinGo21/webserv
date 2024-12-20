/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:46:54 by diego             #+#    #+#             */
/*   Updated: 2024/12/20 10:07:43 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Server.hpp"

Server::Server() {}

Server::Server(const Server &server)
{
	*this = server;
}

Server::~Server() {}

const char	*Server::InvalidFormatException::what() const throw()
{
	return "Invalid parameter format";
}

const std::string	&Server::get_port() const
{
	return this->_port;
}

// void	Server::set_port(const std::string &port)
// {
// 	uint  i = 0;

// 	while (port[i] != '\0')
// 	{
// 		if (!isdigit(port[i]))
// 		{
// 			throw(Server::InvalidFormatException());
// 		}
// 		i++;
// 	}
// 	this->_port = port;
// }

const std::string	&Server::get_host() const
{
	return this->_host;
}

// void	Server::set_host(const std::string &host)
// {
// 	this->_host = host;
// }

const std::string   &Server::get_root() const
{
	return this->_root;
}

// void	Server::set_root(const std::string &root)
// {
// 	this->_root = root;
// }

const std::string	&Server::get_maxSize() const
{
	return this->_maxSize;
}

// void    Server::set_maxSize(const std::string &maxSize)
// {
// 	uint  i = 0;

// 	while (maxSize[i] != '\0')
// 	{
// 		if (!isdigit(maxSize[i]))
// 		{
// 			throw(Server::InvalidFormatException());
// 		}
// 		i++;
// 	}
// 	this->_maxSize = maxSize;
// }

const std::string	&Server::get_errorPage() const
{
	return this->_errorPage;
}

// void	Server::set_errorPage(const std::string &errorPage)
// {
// 	this->_errorPage = errorPage;
// }

const std::string	&Server::get_serverName() const
{
	return this->_serverName;
}

// void    Server::set_serverName(const std::string &serverName)
// {
// 	this->_serverName = serverName;
// }

Server	&Server::operator=(const Server &rhs)
{
	this->_maxSize = rhs._maxSize;
	this->_port = rhs._port;
	this->_host = rhs._host;
	this->_root = rhs._root;
	this->_serverName = rhs._serverName;
	this->_errorPage = rhs._errorPage;
	return *this;
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
