/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_set.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:01:09 by disantam          #+#    #+#             */
/*   Updated: 2025/01/03 16:53:45 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

static size_t	config_set_string(t_webserv &webserv, std::string &var, std::vector<std::string> &tokens, size_t i)
{
	i++;
	if (strchr("{};", tokens[i][0]))
	{
		config_error(webserv, "Syntax Error");
	}
	var = tokens[i];
	return i;
}

static size_t	config_set_autoindex(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	i++;
	if (tokens[i].compare(0, 3, "on") && tokens[i].compare(0, 4, "off"))
	{
		config_error(webserv, "Syntax Error");
	}
	webserv.routes[webserv.routesCount].autoindex = 0;
	if (tokens[i].compare(0, 3, "on"))
	{
		webserv.routes[webserv.routesCount].autoindex = 1;
	}
	return i;
}

static size_t	config_set_methods(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{

}

size_t	config_server_set(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	if (!tokens[i].compare(0, 5, "port"))
	{
		return config_set_string(webserv, webserv.port, tokens, i);
	}
	if (!tokens[i].compare(0, 5, "host"))
	{
		return config_set_string(webserv, webserv.host, tokens, i);
	}
	if (!tokens[i].compare(0, 12, "server_name"))
	{
		return config_set_string(webserv, webserv.serverName, tokens, i);
	}
	if (!tokens[i].compare(0, 9, "max_size"))
	{
		return config_set_string(webserv, webserv.maxSize, tokens, i);
	}
	if (!tokens[i].compare(0, 5, "root"))
	{
		return config_set_string(webserv, webserv.root, tokens, i);
	}
	if (!tokens[i].compare(0, 11, "error_page"))
	{
		return config_set_string(webserv, webserv.errorPage, tokens, i);
	}
	if (tokens[i].compare(0, 6, "route"))
	{
		config_error(webserv, "Unknown parameter");
	}
	return i;
}

size_t	config_route_set(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	if (!tokens[i].compare(0, 5, "root"))
	{
		return config_set_string(webserv, webserv.routes[webserv.routesCount].root, tokens, i);
	}
	if (!tokens[i].compare(0, 6, "index"))
	{
		return config_set_string(webserv, webserv.routes[webserv.routesCount].index, tokens, i);
	}
	if (!tokens[i].compare(0, 7, "return"))
	{
		return config_set_string(webserv, webserv.routes[webserv.routesCount].redir, tokens, i);
	}
	if (!tokens[i].compare(0, 7, "autoindex"))
	{
		return config_set_autoindex(webserv, tokens, i);
	}
	if (!tokens[i].compare(0, 9, "methods"))
	{
		return config_set_methods(webserv, tokens, i);
	}
}

