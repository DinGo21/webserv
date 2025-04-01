/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:57:37 by disantam          #+#    #+#             */
/*   Updated: 2025/03/14 16:31:04 by disantam         ###   ########.fr       */
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
# include "utils.hpp"
# include "classes/Route.hpp"
# include "classes/Server.hpp"

class Config
{
private:
	std::ifstream				_file;
	std::vector<std::string>	_tokens;

	Server	*init_servers(uint i, uint count);
	Route	*init_routes(uint i, uint nServer);
	uint	parse_server(uint &i, uint count);
	uint	parse_route(uint &i, uint routeCount, Route &route);
	int		set_server(uint &i, uint &routeCount, Server &server);
	int		set_route(uint &i, Route &route);
	int		set_server_listen(uint &i, Server &server);
	int		set_server_string(uint &i, Server &server, void (Server::*set)(const std::string &));
	int		set_route_string(uint &i, Route &route, void (Route::*set)(const std::string &));
	int		set_route_methods(uint &i, Route &route);
	int		set_route_autoindex(uint &i, Route &route);

public:
	Server						*servers;

	Config();
	~Config();

	static uint	is_server_directive(const std::string &str);
	static uint	is_route_directive(const std::string &str);

	uint	context_is_closed(uint i);
	int		set_file(const char *path);
	int		read_file();
	int		init();
	int		parse();
	int		check();
	int		check_default_servers(const uint nServer, Server &server);
	int		check_routes(Server &server);
};

# endif