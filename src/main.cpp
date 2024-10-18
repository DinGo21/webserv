/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:56:34 by disantam          #+#    #+#             */
/*   Updated: 2024/10/18 11:05:50 by diego            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "Server.hpp"

void	parse_args(Server &server, std::vector<std::string> &args)
{
	
}

std::vector<std::string>	get_config(std::ifstream &config)
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
	while (i < raw.size())
	{
		while (strchr(" \t\n", raw[i]) && raw[i] != '\0')
			i++;
		if (raw[i] == '\0')
			break ;
		j = raw.find_first_of(" {};\t\n", i);
		if (i - j)
			args.push_back(raw.substr(i, j - i));
		i = j;
		if (strchr(";{}", raw[i]))
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
	return args;
}

int	main(int argc, char *argv[])
{
	Server						server;
	std::ifstream				config;
	std::vector<std::string>	args;

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
	args = get_config(config);
	parse_args(server, args);
	config.close();
	return 0;
}
