/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:09:19 by disantam          #+#    #+#             */
/*   Updated: 2024/11/13 16:05:42 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_H__
# define __SERVER_H__

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <cstring>
# include "Route.hpp"

class Server
{
private:
	std::vector<Route>	_routes;
	size_t				_routesCount;
	size_t				_maxSize;
	std::string			_port;
	std::string			_host;
	std::string			_root;
	std::string			_serverName;
	std::string			_errorPage;

	size_t	route_config_set(std::vector<std::string> &args, size_t i);

public:
	Server();
	~Server();

	size_t		route_config(const std::string &route, std::vector<std::string> &args, size_t i);

	std::string	get_port() const;
	std::string	get_host() const;
	std::string	get_root() const;
	size_t		get_maxSize() const;
	std::string	get_errorPage() const;
	std::string get_serverName() const;
	size_t		set_port(const std::vector<std::string> &args, size_t i);
	size_t		set_host(const std::vector<std::string> &args, size_t i);
	size_t		set_root(const std::vector<std::string> &args, size_t i);
	size_t		set_maxSize(const std::vector<std::string> &args, size_t i);
	size_t		set_errorPage(const std::vector<std::string> &args, size_t i);
	size_t		set_serverName(const std::vector<std::string> &args, size_t i);
};

std::ostream	&operator<<(std::ostream &o, const Server &rhs);

#endif
