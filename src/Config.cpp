/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:28:32 by disantam          #+#    #+#             */
/*   Updated: 2025/01/17 12:06:39 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Config.hpp"

uint	Config::is_server_parameter(const std::string str)
{
	if (str != "port" && str != "host" && str != "root" && str != "max_size" &&
		str != "server_name" && str != "error_page" && str != "route")
	{
		return (0);
	}
	return (1);
}

Config::Config(): _servers(NULL), _file(), _tokens() {}

Config::~Config()
{
	this->_file.close();
	delete [] this->_servers;
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
	for (std::vector<std::string>::iterator it = this->_tokens.begin(); it != this->_tokens.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	return (0);
}


uint	Config::declaration_is_closed(uint i)
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
	return (i);
}

int	Config::server_set_string(uint &i, Server &server, void (Server::*set)(const std::string &))
{
	if (strchr("{};", this->_tokens[++i][0]))
	{
		return (-1);
	}
	try
	{
		std::cout << this->_tokens[i] << std::endl;
		(server.*set)(this->_tokens[i]);
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	if (this->_tokens[++i][0] != ';')
	{
		return (-1);
	}
	return (0);
}

int	Config::server_set(uint &i, uint routeCount, Server &server)
{
	if (this->_tokens[i] == "port")
	{
		return this->server_set_string(i, server, &Server::set_port);
	}
	if (this->_tokens[i] == "host")
	{
		return this->server_set_string(i, server, &Server::set_host);
	}
	if (this->_tokens[i] == "root")
	{
		return this->server_set_string(i, server, &Server::set_root);
	}
	if (this->_tokens[i] == "max_size")
	{
		return this->server_set_string(i, server, &Server::set_maxSize);
	}
	if (this->_tokens[i] == "server_name")
	{
		return this->server_set_string(i, server, &Server::set_serverName);
	}
	if (this->_tokens[i] == "error_page")
	{
		return this->server_set_string(i, server, &Server::set_errorPage);
	}
	if (this->_tokens[i] == "route")
	{
		routeCount = this->parse_route(i, routeCount, server.get_route(routeCount));
	}
	return (0);
}
