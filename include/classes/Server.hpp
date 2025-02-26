/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:09:19 by disantam          #+#    #+#             */
/*   Updated: 2025/02/25 09:46:24 by disantam         ###   ########.fr       */
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
# include "classes/Request.hpp"

typedef struct socket_s
{
	int					on;
	int					serverSock;
	int					maxSock;
	int					ready;
	fd_set				masterSet;
	fd_set				workingSet;
	struct timeval		timeout;
	struct sockaddr_in	addr;
	socklen_t			addrlen;
}					socket_t;

class Server
{
private:
	static uint	_nServers;

	uint		_nRoutes;
	Route		*_routes;
	uint		_port;
	std::string	_host;
	std::string	_root;
	std::string	_maxSize;
	std::string	_serverName;
	std::string	_errorPage;

	int		register_event(socket_t &data);
	int		register_connection(socket_t &data);
	int		register_request(int &i, int &flag);

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

	void	init(socket_t &data);
	int		set_dir();
	int		run(socket_t &sockData);
	int		socket_create(socket_t &data);
	void	socket_close(socket_t &data, int sock);

	static uint			get_nServers();
	uint				get_nRoutes() const;
	Route				&get_route(const uint nRoute) const;
	uint 				get_port() const;
	const std::string	&get_host() const;
	const std::string	&get_root() const;
	const std::string	&get_maxSize() const;
	const std::string	&get_serverName() const;
	const std::string	&get_errorPage() const;
	
	void	set_routes(Route* const routes, const uint nRoutes);
	void	set_port(const uint port);
	void	set_host(const std::string &host);
	void	set_root(const std::string &root);
	void	set_maxSize(const std::string &maxSize);
	void	set_serverName(const std::string &serverName);
	void	set_errorPage(const std::string &errorPage);
};



std::ostream	&operator<<(std::ostream &o, const Server &rhs);

#endif
