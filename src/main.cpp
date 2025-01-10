/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:56:34 by disantam          #+#    #+#             */
/*   Updated: 2025/01/10 12:27:01 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main(int argc, char *argv[])
{
	t_webserv	webserv;

	if (argc != 2)
	{
		std::cerr << "Server requires configuration file" << std::endl;
		return 1;
	}
	init_webserv(webserv);
	config(webserv, argv[1]);
	delete [] webserv.routes;
	return 0;
}
