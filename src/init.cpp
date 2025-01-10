/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:59:46 by disantam          #+#    #+#             */
/*   Updated: 2025/01/10 13:50:58 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void	init_webserv(t_webserv &webserv)
{
	webserv.port = "";
	webserv.host = "";
	webserv.root = "";
	webserv.maxSize = "";
	webserv.errorPage = "";
	webserv.serverName = "";
	webserv.routesCount = 0;
	webserv.routes = NULL;
}

void	init_route(t_route &route)
{
	route.path = "";
	route.root = "";
	route.index = "";
	route.redir = "";
	route.autoindex = 0;
	route.methods[GET] = 0;
	route.methods[POST] = 0;
}
