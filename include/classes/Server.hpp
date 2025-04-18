/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:09:19 by disantam          #+#    #+#             */
/*   Updated: 2025/04/01 16:23:54 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_H__
# define __SERVER_H__

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <cstdlib>
# include <stdexcept>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include "classes/Route.hpp"

class Server
{
private:
	static uint	_nServers;

	uint		_nRoutes;
	Route		*_routes;
	bool		_default;
	std::string	_port;
	std::string	_host;
	std::string	_root;
	std::string	_maxSize;
	std::string	_serverName;
	std::string	_errorPage;

	// int		register_event(socket_t &data);
	// int		register_connection(socket_t &data);
	// int		register_request(int &i, int &flag);

public:
	class InvalidFormatException: public std::exception
	{
	public:
		virtual const char	*what() const throw();
	};

	class OutOfBoundsException: public std::exception
	{
	public:
		virtual const char	*what() const throw();
	};

	Server();
	~Server();
	
	static uint			get_nServers();
	uint				get_nRoutes() const;
	Route				&get_route(const uint nRoute) const;
	const std::string 	&get_port() const;
	const std::string	&get_host() const;
	const std::string	&get_root() const;
	const std::string	&get_maxSize() const;
	const std::string	&get_serverName() const;
	const std::string	&get_errorPage() const;
	bool				isdefault() const;
	
	void	set_default();
	void	set_routes(Route* const routes, const uint nRoutes);
	void	set_port(const std::string &port);
	void	set_host(const std::string &host);
	void	set_root(const std::string &root);
	void	set_maxSize(const std::string &maxSize);
	void	set_serverName(const std::string &serverName);
	void	set_errorPage(const std::string &errorPage);
};

std::ostream	&operator<<(std::ostream &o, const Server &rhs);

#endif
