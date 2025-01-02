/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:59:46 by disantam          #+#    #+#             */
/*   Updated: 2025/01/02 13:19:56 by disantam         ###   ########.fr       */
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
