/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_set.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:01:09 by disantam          #+#    #+#             */
/*   Updated: 2025/01/02 16:05:25 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

static size_t	config_set_var(std::string &var, std::vector<std::string> &tokens, size_t i)
{
	i++;
	if (strchr("{};", tokens[i][0]))
	{
		std::cerr << "Syntax error: " << tokens[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	var = tokens[i];
	return i;
}

size_t	config_server_set(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	if (!tokens[i].compare(0, 5, "port"))
	{
		return config_set_var(webserv.port, tokens, i);
	}
	if (!tokens[i].compare(0, 5, "host"))
	{
		return config_set_var(webserv.host, tokens, i);
	}
	if (!tokens[i].compare(0, 12, "server_name"))
	{
		return config_set_var(webserv.serverName, tokens, i);
	}
	if (!tokens[i].compare(0, 9, "max_size"))
	{
		return config_set_var(webserv.maxSize, tokens, i);
	}
	if (!tokens[i].compare(0, 5, "root"))
	{
		return config_set_var(webserv.root, tokens, i);
	}
	if (!tokens[i].compare(0, 11, "error_page"))
	{
		return config_set_var(webserv.errorPage, tokens, i);
	}
	if (tokens[i].compare(0, 6, "route"))
	{
		std::cerr << "Unknown parameter: " << tokens[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	return i;
}
