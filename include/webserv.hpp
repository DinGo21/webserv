/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:24:17 by disantam          #+#    #+#             */
/*   Updated: 2024/11/18 15:28:49 by disantam         ###   ########.fr       */
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

/*Configs*/

void	server_config(Server &server, char *path);
size_t	server_config_set_port(Server &server, const std::vector<std::string> &args, size_t i);
size_t	server_config_set_host(Server &server, const std::vector<std::string> &args, size_t i);
size_t	server_config_set_root(Server &server, const std::vector<std::string> &args, size_t i);
size_t	server_config_set_maxSize(Server &server, const std::vector<std::string> &args, size_t i);
size_t	server_config_set_errorPage(Server &server, const std::vector<std::string> &args, size_t i);
size_t	server_config_set_serverName(Server &server, const std::vector<std::string> &args, size_t i);

#endif
