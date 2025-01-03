/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:56:20 by disantam          #+#    #+#             */
/*   Updated: 2025/01/03 13:03:46 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void	config_error(t_webserv &webserv, const std::string &err_message)
{
	if (webserv.routes != NULL)
	{
		delete webserv.routes;
	}
	std::cerr << err_message << std::endl;
	exit(EXIT_FAILURE);
}