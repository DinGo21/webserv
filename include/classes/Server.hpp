/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:09:19 by disantam          #+#    #+#             */
/*   Updated: 2025/01/17 11:25:08 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_H__
# define __SERVER_H__

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <stdexcept>
# include "classes/Route.hpp"

class Server
{
private:
	static uint	_nServers;

	uint		_nRoutes;
	Route		*_routes;
	std::string	_port;
	std::string	_host;
	std::string	_root;
	std::string	_maxSize;
	std::string	_serverName;
	std::string	_errorPage;

public:
	Server();
	~Server();

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

	static uint	get_nServers();
	
	Route	&get_route(const uint nRoute) const;
	
	void	set_routes(Route* const routes, const uint nRoutes);
	void	set_port(const std::string &port);
	void	set_host(const std::string &host);
	void	set_root(const std::string &root);
	void	set_maxSize(const std::string &maxSize);
	void	set_serverName(const std::string &serverName);
	void	set_errorPage(const std::string &errorPage);

};

#endif
