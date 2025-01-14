/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:56:34 by disantam          #+#    #+#             */
/*   Updated: 2025/01/14 12:26:03 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void	create_server(t_config &conf)
{
	Server	*servers;

	
}

int	main(int argc, char *argv[])
{
	t_config	conf;

	if (argc != 2)
	{
		std::cerr << "No arguments passed, using default configuration file" << std::endl;
		return 1;
	}
	config(conf, argv[1]);
	create_server(conf);
	delete [] conf.webserv;
	return 0;
}
