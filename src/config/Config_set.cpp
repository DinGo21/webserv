/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config_set.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:53:47 by disantam          #+#    #+#             */
/*   Updated: 2025/03/14 16:50:07 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Config.hpp"

int	Config::set_route_autoindex(uint &i, Route &route)
{
	if (strchr("{};", this->_tokens[++i][0]) && this->_tokens[i] != "ON" &&
		this->_tokens[i] != "OFF")
	{
		std::cerr << "Invalid token: '" << this->_tokens[i] << '\'' << std::endl;
		return (-1);
	}
	if (this->_tokens[i] == "ON")
	{
		route.set_autoindex(1);
	}
	if (this->_tokens[++i][0] != ';')
	{
		std::cerr << "Unexpected token: " << this->_tokens[i] << "', expected ';'" << std::endl;
		return (-1);
	}
	return (0);
}

int	Config::set_route_methods(uint &i, Route &route)
{
	if (strchr("{};", this->_tokens[++i][0]))
	{
		std::cerr << "Invalid token: '" << this->_tokens[i] << '\'' << std::endl;
		return (-1);
	}
	while (is_method(this->_tokens[i]) && this->_tokens[i][0] != ';')
	{
		if (this->_tokens[i] == "GET")
		{
			route.set_method(GET);
		}
		if (this->_tokens[i] == "POST")
		{
			route.set_method(POST);
		}
		if (this->_tokens[i] == "DELETE")
		{
			route.set_method(DELETE);
		}
		i++;
	}
	if (this->_tokens[i][0] != ';')
	{
		std::cerr << "Unexpected token: " << this->_tokens[i] << "', expected ';'" << std::endl;
		return (-1);
	}
	return (0);
}

int	Config::set_route_string(uint &i, Route &route, void (Route::*set)(const std::string &))
{
	if (strchr("{};", this->_tokens[++i][0]))
	{
		std::cerr << "Invalid token: '" << this->_tokens[i] << '\'' << std::endl;
		return (-1);
	}
	try
	{
		(route.*set)(this->_tokens[i]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	if (this->_tokens[++i][0] != ';')
	{
		std::cerr << "Unexpected token: " << this->_tokens[i] << "', expected ';'" << std::endl;
		return (-1);
	}
	return (0);
}

int	Config::set_route(uint &i, Route &route)
{
	if (this->_tokens[i] == "root")
	{
		return this->set_route_string(i, route, &Route::set_root); 
	}
	if (this->_tokens[i] == "index")
	{
		return this->set_route_string(i, route, &Route::set_index); 
	}
	if (this->_tokens[i] == "redir")
	{
		return this->set_route_string(i, route, &Route::set_redir); 
	}
	if (this->_tokens[i] == "methods")
	{
		return this->set_route_methods(i, route);
	}
	if (this->_tokens[i] == "autoindex")
	{
		return this->set_route_autoindex(i, route);
	}
	return (0);
}

int	Config::set_server_string(uint &i, Server &server, void (Server::*set)(const std::string &))
{
	if (strchr("{};", this->_tokens[++i][0]))
	{
		std::cerr << "Invalid token: '" << this->_tokens[i] << '\'' << std::endl;
		return (-1);
	}
	try
	{
		(server.*set)(this->_tokens[i]);
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	if (this->_tokens[++i][0] != ';')
	{
		std::cerr << "Unexpected token: " << this->_tokens[i] << "', expected ';'" << std::endl;
		return (-1);
	}
	return (0);
}

int	Config::set_server_listen(uint &i, Server &server)
{
	uint	pos;

	if (strchr("{};", this->_tokens[++i][0]))
	{
		std::cerr << "Invalid token: '" << this->_tokens[i] << '\'' << std::endl;
		return (-1);
	}
	pos = this->_tokens[i].find(':');
	try
	{
		if (pos == std::string::npos)
		{
			server.set_port(this->_tokens[i]);
			server.set_host("127.0.0.1");
		}
		else
		{
			server.set_host(this->_tokens[i].substr(0, pos));
			server.set_port(this->_tokens[i].substr(pos + 1, this->_tokens[i].size() - pos));
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	if (this->_tokens[++i][0] != ';')
	{
		std::cerr << "Unexpected token: " << this->_tokens[i] << "', expected ';'" << std::endl;
		return (-1);
	}
	return (0);
}

int	Config::set_server(uint &i, uint &routeCount, Server &server)
{
	if (this->_tokens[i] == "listen")
	{
		return this->set_server_listen(i, server);
	}
	if (this->_tokens[i] == "root")
	{
		return this->set_server_string(i, server, &Server::set_root);
	}
	if (this->_tokens[i] == "max_size")
	{
		return this->set_server_string(i, server, &Server::set_maxSize);
	}
	if (this->_tokens[i] == "server_name")
	{
		return this->set_server_string(i, server, &Server::set_serverName);
	}
	if (this->_tokens[i] == "error_page")
	{
		return this->set_server_string(i, server, &Server::set_errorPage);
	}
	if (this->_tokens[i] == "route")
	{
		routeCount = this->parse_route(i, routeCount, server.get_route(routeCount));
		if (routeCount == 0)
			return (-1);
	}
	return (0);
}
