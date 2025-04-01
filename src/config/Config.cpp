/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:28:32 by disantam          #+#    #+#             */
/*   Updated: 2025/03/17 14:49:48 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Config.hpp"

uint	Config::is_server_directive(const std::string &str)
{
	if (str != "listen" && str != "root" && str != "max_size" &&
		str != "server_name" && str != "error_page" && str != "route")
	{
		return (0);
	}
	return (1);
}

uint	Config::is_route_directive(const std::string &str)
{
	if (str != "index" && str != "root" && str != "autoindex" && str != "methods" &&
		str != "redir")
	{
		return (0);
	}
	return (1);
}

Config::Config(): _file(), _tokens(), servers(NULL) {}

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
	size_t		i = 0;
	size_t		j = 0;
	std::string	tmp;
	std::string	raw;

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

uint	Config::context_is_closed(uint i)
{
	uint	f = 1;

	if (i < this->_tokens.size() && this->_tokens[i][0] != '{')
	{
		return (0);
	}
	while (++i < this->_tokens.size() && f != 0)
	{
		if (this->_tokens[i][0] == '{')
			f++;
		if (this->_tokens[i][0] == '}')
			f--;
	}
	if (f != 0)
	{
		return (0);
	}
	return (i - 1);
}
