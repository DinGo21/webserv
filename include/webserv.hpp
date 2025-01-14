/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:24:17 by disantam          #+#    #+#             */
/*   Updated: 2025/01/13 10:49:36 by disantam         ###   ########.fr       */
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
# include "defs/structs.hpp"
# include "classes/Route.hpp"
# include "classes/Server.hpp"

/*init*/

void	init_webserv(t_webserv &webserv);
void	init_route(t_route &route);

/*errors*/

void	config_error(t_webserv &webserv, const std::string &err_message);

/*configs*/

void	config(t_config &conf, char *path);
size_t	config_server_set(t_webserv &webserv, std::vector<std::string> &tokens, size_t i);
size_t	config_route_set(t_webserv &webserv, std::vector<std::string> &tokens, size_t i);

// size_t	config_set_value(std::string &str, const std::vector<std::string> &args, size_t i);

#endif
