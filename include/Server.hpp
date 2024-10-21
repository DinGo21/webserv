/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:09:19 by disantam          #+#    #+#             */
/*   Updated: 2024/10/21 13:56:46 by diego            ###   ########.fr       */
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
	size_t		_host;
	size_t		_maxSize;
	std::string	_serverName;
	std::string	_errorPage;
	std::string	_root;

public:
	Server();
	~Server();

	uint		get_port() const;
	void		set_port(const uint &port);
	size_t		get_host() const;
	void		set_host(const size_t &host);
	std::string	set_maxSize() const;
	void		set_maxSize(const std::string &maxSize);
	std::string	get_errorPage() const;
	void		set_errorPage(const std::string &errorPage);
	std::string get_root() const;
	void		set_root(const std::string &root);
};

#endif