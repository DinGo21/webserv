/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config_check.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:49:18 by disantam          #+#    #+#             */
/*   Updated: 2025/03/17 14:49:50 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Config.hpp"

int	Config::check_default_servers(const uint nServer, Server &server)
{
	for (uint i = 0; i < Server::get_nServers(); i++)
	{
		if (i != nServer && server.get_port() == this->servers[i].get_port()
			&& server.get_host() == this->servers[i].get_host() && this->servers[i].isdefault())
		{
			return (0);
		}
	}
	server.set_default();
	return (0);
}

int	Config::check_routes(Server &server)
{
	Route	*route;

	for (uint j = 0; j < server.get_nRoutes(); j++)
	{
		route = &server.get_route(j);
		if (!route->get_path().size() || !route->get_redir().size())
		{
			std::cerr << "Route is missing directives" << std::endl;
			return (-1);
		}
		if (!route->method_isset(GET) && !route->method_isset(POST)
			&& !route->method_isset(DELETE))
		{
			route->set_method(GET);
		}
		if (!route->get_root().size())
		{
			route->set_root(server.get_root());
		}
		if (!route->get_index().size())
		{
			route->set_root("index.html");
		}
	}
	return (0);
}

int	Config::check()
{
	for (uint i = 0; i < Server::get_nServers(); i++)
	{
		if (!this->servers[i].get_port().size() || !this->servers[i].get_host().size()
			|| !this->servers[i].get_root().size() || !this->servers[i].get_maxSize().size()
			|| !this->servers[i].get_serverName().size() || !this->servers[i].get_errorPage().size())
		{
			std::cerr << "Server is missing directives" << std::endl;
			return (-1);
		}
		this->check_routes(this->servers[i]);
		this->check_default_servers(i, this->servers[i]);
	}
	return (0);
}
