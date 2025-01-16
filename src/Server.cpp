/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:46:54 by diego             #+#    #+#             */
/*   Updated: 2025/01/16 09:39:58 by disantam         ###   ########.fr       */
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
	return "Invalid parameter format";
}

void	Server::set_routes(Route* const routes, const uint nRoutes)
{
	this->_routes = routes;
	this->_nRoutes = nRoutes;
}
