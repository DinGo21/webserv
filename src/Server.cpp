/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:46:54 by diego             #+#    #+#             */
/*   Updated: 2024/10/30 11:28:47 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Server.hpp"

Server::Server(): _routes(), _port(0), _maxSize(0) {}

Server::~Server() {}

uint    Server::get_port() const
{
    return this->_port;
}

void	Server::set_port(const uint &port)
{
    this->_port = port;
}

std::string	Server::get_host() const
{
    return this->_host;
}

void	Server::set_host(const std::string &host)
{
    this->_host = host;
}

size_t	Server::get_maxSize() const
{
    return this->_maxSize;
}

void    Server::set_maxSize(const size_t &maxSize)
{
    this->_maxSize = maxSize;
}

std::string Server::get_serverName() const
{
    return this->_serverName;
}

void    Server::set_serverName(const std::string &serverName)
{
    this->_serverName = serverName;
}

std::string Server::get_errorPage() const
{
    return this->_errorPage;
}

void	Server::set_errorPage(const std::string &errorPage)
{
    this->_errorPage = errorPage;
}

std::string   Server::get_root() const
{
    return this->_root;
}

void	Server::set_root(const std::string &root)
{
    this->_root = root;
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
