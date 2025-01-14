/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:28:32 by disantam          #+#    #+#             */
/*   Updated: 2025/01/14 16:55:57 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Config.hpp"

Config::Config()
{

}

Config::~Config()
{
	this->_file.close();
}

int	Config::set_file(const char *path)
{
	this->_file.open(path);
	if (!this->_file.is_open())
	{
		std::cerr << "Unable to open configuration file" << std::endl;
		return (-1);
	}
	return (0);
}

int	Config::read_file()
{
	size_t						i = 0;
	size_t						j = 0;
	std::string					tmp;
	std::string					raw;

	while (std::getline(this->_file, tmp))
	{
		raw += tmp;
		raw.push_back('\n');
	}
	while (raw[i] != '\0')
	{
		while (strchr(" \t\n", raw[i]) && raw[i] != '\0')
			i++;
		if (raw[i] == '\0')
			break ;
		j = raw.find_first_of(" {};\t\n", i);
		if (i - j)
			this->_tokens.push_back(raw.substr(i, j - i));
		i = j;
		if (strchr(";{}", raw[i]))
		{
			this->_tokens.push_back(raw.substr(i, 1));
			i++;
		}
	}
	return (0);
}

int	Config::init_server()
{
	uint	i = 0;
	uint	count = 0;

	while (i < this->_tokens.size())
	{
		if (_tokens[i] == "server")
		{
			count++;
		}
		i++;
	}
	this->_servers = new Server[count];
	if (!this->_servers)
	{
		std::cerr << "Could not initialize server" << std::endl;
		return (-1);
	}
	return (0);
}
