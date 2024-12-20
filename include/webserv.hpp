/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:24:17 by disantam          #+#    #+#             */
/*   Updated: 2024/12/20 16:34:18 by disantam         ###   ########.fr       */
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

/*Utils*/
uint	config_check_brackets(std::vector<std::string> &args, size_t i);

/*Configs*/

typedef	struct	s_webserv
{
	std::string	maxSize;
	std::string	port;
	std::string	host;
	std::string	root;
	std::string	serverName;
	std::string	errorPage;
} 				t_webserv;

typedef struct 	s_route
{
	std::string	root;
	std::string	index;
	std::string	redir;
	std::string	methods[2];
	bool		autoindex;
}				t_route;

void	config(t_webserv *webserv, char *path);
size_t	config_route(t_webserv *webserv, std::vector<std::string> &args, size_t i);
// size_t	config_set_value(std::string &str, const std::vector<std::string> &args, size_t i);

#endif
