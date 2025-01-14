/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:15:55 by disantam          #+#    #+#             */
/*   Updated: 2025/01/13 10:48:34 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STRUCTS_H__
# define __STRUCTS_H__

# include <iostream>

enum e_method
{
	GET,
	POST
};

typedef struct 	s_route
{
	std::string path;
	std::string	root;
	std::string	index;
	std::string	redir;
	bool		methods[2];
	bool		autoindex;
}				t_route;

typedef	struct	s_webserv
{
	std::string	port;
	std::string	host;
	std::string	root;
	std::string	maxSize;
	std::string	errorPage;
	std::string	serverName;
	uint		routesCount;
	t_route		*routes;

} 				t_webserv;

typedef struct s_config
{
	uint		serverCount;
	t_webserv	*webserv;
}				t_config;

#endif