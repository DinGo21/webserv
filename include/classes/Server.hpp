/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:09:19 by disantam          #+#    #+#             */
/*   Updated: 2025/01/14 15:17:39 by disantam         ###   ########.fr       */
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

protected:
	static uint	_nServers;

	std::string	_maxSize;
	std::string	_port;
	std::string	_host;
	std::string	_root;
	std::string	_serverName;
	std::string	_errorPage;

public:
	Server();
	virtual ~Server();

	class InvalidFormatException: public std::exception
	{
	public:
		virtual const char	*what() const throw();
	};

	static uint	get_nServers();
};

#endif
