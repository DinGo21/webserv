/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:09:19 by disantam          #+#    #+#             */
/*   Updated: 2024/11/18 16:13:43 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_H__
# define __SERVER_H__

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <stdexcept>

class Server
{
private:
	std::string	_maxSize;
	std::string	_port;
	std::string	_host;
	std::string	_root;
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

	const std::string	&get_port() const;
	const std::string	&get_host() const;
	const std::string	&get_root() const;
	const std::string	&get_maxSize() const;
	const std::string	&get_errorPage() const;
	const std::string	&get_serverName() const;
	void				set_port(const std::string &port);
	void				set_host(const std::string &host);
	void				set_root(const std::string &root);
	void				set_maxSize(const std::string &maxSize);
	void				set_errorPage(const std::string &errorPage);
	void				set_serverName(const std::string &serverName);
};

std::ostream	&operator<<(std::ostream &o, const Server &rhs);

#endif
