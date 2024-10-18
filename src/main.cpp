/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:56:34 by disantam          #+#    #+#             */
/*   Updated: 2024/10/16 16:34:35 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "Server.hpp"

int	get_config(std::ifstream &config)
{
	size_t						i = 0;
	size_t						j = 0;
	std::string					tmp;
	std::string					raw;
	std::vector<std::string>	args;	

	while (std::getline(config, tmp))
	{
		raw += tmp;
		raw.push_back('\n');
	}
	std::cout << raw << std::endl;
	std::cout << raw.size() << std::endl;
	while (i < raw.size())
	{
		while (strchr(" \t\n", raw[i]) != NULL && raw[i] != '\0')
			i++;
		if (raw[i] == '\0')
			break ;
		j = raw.find_first_of(" {};\t\n", i);
		std::cout << raw[j] << ' ' << j << std::endl;
		args.push_back(raw.substr(i, j - i));
		i = j;
		if (raw[i] == '{' || raw[i] == '}')
		{
			args.push_back(raw.substr(i, 1));
			i++;
		}
		if (raw[i] == ';')
			i++;
	}
	for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	return 0;
}

int	main(int argc, char *argv[])
{
	// Server			server;
	std::ifstream	config;

	if (argc != 2)
	{
		std::cerr << "Server requires configuration file." << std::endl;
		return 1;
	}
	config.open(argv[1]);
	if (!config.is_open())
	{
		std::cerr << "Unable to open file: " << argv[1] << std::endl;
		return 1;
	}
	if (get_config(config))
	{
		return 1;
	}
	return 0;
}
