/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config_parse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:24:24 by disantam          #+#    #+#             */
/*   Updated: 2025/03/13 12:55:08 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Config.hpp"

uint	Config::parse_route(uint &i, uint routeCount, Route &route)
{
	uint	end = 0;

	if (strchr("{};", this->_tokens[++i][0]))
	{
		std::cerr << "Expected a route path" << std::endl;
		return (0);
	}
	route.set_path(this->_tokens[i]);
	end = this->context_is_closed(++i);
	if (end == 0)
		return (0);
	while (++i < end)
	{
		if (!Config::is_route_directive(this->_tokens[i]))
		{
			std::cerr << "Unknown directive: '" << this->_tokens[i] << '\'' << std::endl;
			return (0);
		}
		if (this->set_route(i, route) < 0)
			return (0);
	}
	return (routeCount + 1);
}

uint	Config::parse_server(uint &i, uint count)
{
	uint	end = this->context_is_closed(++i);
	uint	routeCount = 0;

	if (end == 0)
		return (0);
	while (++i < end)
	{
		if (!Config::is_server_directive(this->_tokens[i]))
		{
			std::cerr << "Unknown directive: '" << this->_tokens[i] << '\'' << std::endl;
			return (0);
		}
		if (this->set_server(i, routeCount, this->servers[count]) < 0)
			return (0);
	}
	return (count + 1);
}

int	Config::parse()
{
	uint	i = 0;
	uint	count = 0;
	
	while (count < Server::get_nServers())
	{
		while (this->_tokens[i] != "server" && this->_tokens[i][0] == ';')
			i++;
		if (this->_tokens[i] != "server")
		{
			std::cerr << "Invalid block directive: '" << this->_tokens[i] << '\'' << std::endl;
			return (-1);
		}
		count = this->parse_server(i, count);
		if (count == 0)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
