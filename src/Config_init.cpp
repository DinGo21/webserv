/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config_init.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:01:02 by disantam          #+#    #+#             */
/*   Updated: 2025/01/16 09:55:07 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Config.hpp"

Route	*Config::init_routes(uint i, uint nServer)
{
	uint	end = declaration_is_closed(i++);
	uint	count = 0;
	Route	*routes = NULL;

	if (end == 0)
	{
		return (NULL);
	}
	while (i < end)
	{
		if (this->_tokens[i] == "route")
		{
			count++;
		}
		i++;
	}
	routes = new Route[count];
	if (!routes)
	{
		return (NULL);
	}
	this->_servers[nServer].set_routes(routes, count);
	return (routes);
}

Server	*Config::init_servers(uint i, uint count)
{
	while (i < this->_tokens.size() && this->_tokens[i] != "server")
		i++;
	if (i >= this->_tokens.size())
	{
		this->_servers = new Server[count];
		if (!this->_servers)
		{
			return (NULL);
		}
		return (this->_servers);
	}
	if (this->_tokens[i] == "server")
	{
		if (!this->init_servers(i + 1, count + 1))
			return NULL;
	}
	if (!init_routes(i + 1, count))
		return (NULL);
	return (this->_servers);
}

int	Config::init()
{
	if (!this->init_servers(0, 0))
	{
		std::cerr << "memory allocation error" << std::endl;
		return (-1);
	}
	if (Server::get_nServers() == 0)
	{
		std::cerr << "Could not configure any server" << std::endl;
		return (-1);
	}
	return (0);
}
