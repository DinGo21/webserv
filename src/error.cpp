/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:56:20 by disantam          #+#    #+#             */
/*   Updated: 2025/01/10 11:46:33 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void	config_error(t_webserv &webserv, const std::string &err_message)
{
	if (webserv.routes != NULL)
	{
		delete [] webserv.routes;
	}
	std::cerr << err_message << std::endl;
	exit(EXIT_FAILURE);
}