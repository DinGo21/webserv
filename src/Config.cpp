/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:28:32 by disantam          #+#    #+#             */
/*   Updated: 2025/01/15 21:19:10 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Config.hpp"

Config::Config(): _servers(), _file(), _tokens() {}

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
	return (0);
}

int	Config::declaration_is_closed(uint i)
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

Route	*Config::init_routes(uint i, uint nServer)
{
	uint	end = declaration_is_closed(i++);
	uint	count = 0;
	Route	*routes = NULL;

	if (end == 0)
	{
		return (NULL);
	}
	while (i < end)
	{
		if (this->_tokens[i] == "route")
		{
			count++;
		}
		i++;
	}
	routes = new Route[count];
	if (!routes)
	{
		return (NULL);
	}
	this->_servers[nServer].set_routes(routes, count);
	std::cout << "created " << count << " routes for server " << nServer << std::endl;
	return (routes);
}

Server	*Config::init_servers(uint i, uint count)
{
	while (i < this->_tokens.size() && this->_tokens[i] != "server")
		i++;
	if (i >= this->_tokens.size())
	{
		this->_servers = new Server[count];
		if (!this->_servers)
		{
			return (NULL);
		}
		return (this->_servers);
	}
	if (this->_tokens[i] == "server")
	{
		if (!this->init_servers(i + 1, count + 1))
			return NULL;
	}
	std::cout << "server " << count << " has been created" << std::endl; 
	if (!init_routes(i + 1, count))
		return (NULL);
	return (this->_servers);
}

int	Config::init()
{
	if (!this->init_servers(0, 0))
	{
		std::cerr << "memory allocation error" << std::endl;
		return (-1);
	}
	if (Server::get_nServers() == 0)
	{
		std::cerr << "Could not configure any server" << std::endl;
		return (-1);
	}
	return (0);
	// for (uint i = 0; i < this->_tokens.size(); i++)
	// {
	// 	if (this->_tokens[i] == "server")
	// 	{
	// 		count++;
	// 	}
	// }
	// this->_servers = new Server[count];
	// if (!this->_servers)
	// {
	// 	std::cerr << "Could not initialize server" << std::endl;
	// 	return (-1);
	// }
}
