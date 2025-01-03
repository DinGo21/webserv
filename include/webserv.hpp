/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:24:17 by disantam          #+#    #+#             */
/*   Updated: 2025/01/03 14:26:59 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WEBSERV_H__
# define __WEBSERV_H__

# include <iostream>
# include <fstream>
# include <cstdlib>
# include <cstring>
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include "classes/Route.hpp"
# include "classes/Server.hpp"

typedef struct 	s_route
{
	std::string path;
	std::string	root;
	std::string	index;
	std::string	redir;
	std::string	methods[2];
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

/*init*/

void	init_webserv(t_webserv &webserv);

/*errors*/

void	config_error(t_webserv &webserv, const std::string &err_message);

/*Configs*/

void	config(t_webserv &webserv, char *path);
size_t	config_server_set(t_webserv &webserv, std::vector<std::string> &tokens, size_t i);
// size_t	config_set_value(std::string &str, const std::vector<std::string> &args, size_t i);

#endif
