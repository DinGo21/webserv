/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_set.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:01:09 by disantam          #+#    #+#             */
/*   Updated: 2025/01/13 09:37:40 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

static size_t	config_set_string(t_webserv &webserv, std::string &var, std::vector<std::string> &tokens, size_t i)
{
	i++;
	if (strchr("{};", tokens[i][0]) || tokens[i + 1][0] != ';')
	{
		config_error(webserv, "Syntax Error");
	}
	var = tokens[i];
	return i;
}

static size_t	config_set_autoindex(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	i++;
	if (tokens[i] != "ON" && tokens[i] != "OFF")
	{
		config_error(webserv, "Syntax Error");
	}
	webserv.routes[webserv.routesCount].autoindex = 0;
	if (tokens[i] == "ON")
	{
		webserv.routes[webserv.routesCount].autoindex = 1;
	}
	return i;
}

static size_t	config_set_methods(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	size_t	j = ++i + 2;

	while (i < j && tokens[i][0] != ';')
	{
		if (tokens[i] != "GET" && tokens[i] != "POST" && tokens[i][0] != ';')
		{
			config_error(webserv, "Syntax Error");
		}
		if (tokens[i] == "GET")	
			webserv.routes[webserv.routesCount].methods[GET] = 1;
		if (tokens[i] == "POST")
			webserv.routes[webserv.routesCount].methods[POST] = 1;
		i++;
	}
	return i;
}

size_t	config_server_set(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	if (tokens[i] == "port")
	{
		return config_set_string(webserv, webserv.port, tokens, i);
	}
	if (tokens[i] == "host")
	{
		return config_set_string(webserv, webserv.host, tokens, i);
	}
	if (tokens[i] == "server_name")
	{
		return config_set_string(webserv, webserv.serverName, tokens, i);
	}
	if (tokens[i] == "max_size")
	{
		return config_set_string(webserv, webserv.maxSize, tokens, i);
	}
	if (tokens[i] == "root")
	{
		return config_set_string(webserv, webserv.root, tokens, i);
	}
	if (tokens[i] == "error_page")
	{
		return config_set_string(webserv, webserv.errorPage, tokens, i);
	}
	if (tokens[i] != "route")
	{
		config_error(webserv, "Unknown parameter");
	}
	return i;
}

size_t	config_route_set(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	if (tokens[i] == "root")
	{
		return config_set_string(webserv, webserv.routes[webserv.routesCount].root, tokens, i);
	}
	if (tokens[i] == "index")
	{
		return config_set_string(webserv, webserv.routes[webserv.routesCount].index, tokens, i);
	}
	if (tokens[i] == "redir")
	{
		return config_set_string(webserv, webserv.routes[webserv.routesCount].redir, tokens, i);
	}
	if (tokens[i] == "autoindex")
	{
		return config_set_autoindex(webserv, tokens, i);
	}
	if (tokens[i] == "methods")
	{
		return config_set_methods(webserv, tokens, i);
	}
	if (strchr("{};", tokens[i][0]))
	{
		config_error(webserv, "Unknown parameter");
	}
	return i;
}

