/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:57:37 by disantam          #+#    #+#             */
/*   Updated: 2025/01/17 12:06:20 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CONFIG_H__
# define __CONFIG_H__

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <cstdlib>
# include <cstring>
# include <stdexcept>
# include "classes/Route.hpp"
# include "classes/Server.hpp"

class	Config
{
private:
	Server						*_servers;
	std::ifstream				_file;
	std::vector<std::string>	_tokens;

	Server	*init_servers(uint i, uint count);
	Route	*init_routes(uint i, uint nServer);

	uint	parse_server(uint &i, uint count);
	uint	parse_route(uint &i, uint routeCount, Route &route);
	int		server_set(uint &i, uint routeCount, Server &server);
	int		server_set_string(uint &i, Server &server, void (Server::*set)(const std::string &));

public:
	Config();
	~Config();

	static uint	is_server_parameter(const std::string str);

	uint	declaration_is_closed(uint i);
	int		set_file(const char *path);
	int		read_file();
	int		init();
	int		parse();
};

# endif