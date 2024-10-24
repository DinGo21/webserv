/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:09:19 by disantam          #+#    #+#             */
/*   Updated: 2024/10/23 08:16:09 by diego            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_H__
# define __SERVER_H__

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>

class Server
{
private:
	uint		_port;
	size_t		_maxSize;
	std::string	_host;
	std::string	_serverName;
	std::string	_errorPage;
	std::string	_root;

public:
	Server();
	~Server();

	uint		get_port() const;
	void		set_port(const uint &port);
	size_t		get_maxSize() const;
	void		set_maxSize(const size_t &maxSize);
	std::string	get_host() const;
	void		set_host(const std::string &host);
	std::string get_serverName() const;
	void		set_serverName(const std::string &serverName);
	std::string	get_errorPage() const;
	void		set_errorPage(const std::string &errorPage);
	std::string	get_root() const;
	void		set_root(const std::string &root);
};

std::ostream	&operator<<(std::ostream &o, const Server &rhs);

#endif
