/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_routes.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:36:24 by disantam          #+#    #+#             */
/*   Updated: 2024/12/20 16:49:20 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

size_t	config_route(t_webserv *webserv, std::vector<std::string> &args, size_t i)
{
	i++;
	if (args[i][0] != '/')
	{
		std::cerr << args[i] << " is not a route" << std::endl;
	}
}