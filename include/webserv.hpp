/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:24:17 by disantam          #+#    #+#             */
/*   Updated: 2024/10/24 14:45:48 by diego            ###   ########.fr       */
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
# include "classes/Server.hpp"

/*Configs*/

uint	server_config_set_port(Server &server, std::vector<std::string> &args, size_t i);
uint	server_config_set_root(Server &server, std::vector<std::string> &args, size_t i);
uint	server_config_set_host(Server &server, std::vector<std::string> &args, size_t i);
uint	server_config_set_maxSize(Server &server, std::vector<std::string> &args, size_t i);
uint	server_config_set_errorPage(Server &server, std::vector<std::string> &args, size_t i);
uint	server_config_set_serverName(Server &server, std::vector<std::string> &args, size_t i);

#endif
