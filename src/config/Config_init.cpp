/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config_init.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:01:02 by disantam          #+#    #+#             */
/*   Updated: 2025/03/14 15:50:14 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Config.hpp"

Route	*Config::init_routes(uint i, uint nServer)
{
	uint	end = this->context_is_closed(i++);
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
	this->servers[nServer].set_routes(routes, count);
	return (routes);
}

Server	*Config::init_servers(uint i, uint count)
{
	while (i < this->_tokens.size() && this->_tokens[i] != "server")
		i++;
	if (i >= this->_tokens.size())
	{
		this->servers = new Server[count];
		if (!this->servers)
		{
			return (NULL);
		}
		return (this->servers);
	}
	if (this->_tokens[i] == "server")
	{
		if (!this->init_servers(i + 1, count + 1))
			return (NULL);
	}
	if (!init_routes(i + 1, count))
		return (NULL);
	return (this->servers);
}

int	Config::init()
{
	if (!this->init_servers(0, 0))
	{
		std::cerr << "Memory allocation error" << std::endl;
		return (-1);
	}
	if (Server::get_nServers() == 0)
	{
		std::cerr << "Empty configuration file" << std::endl;
		return (-1);
	}
	return (0);
}
