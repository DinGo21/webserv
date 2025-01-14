/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:29:21 by disantam          #+#    #+#             */
/*   Updated: 2025/01/13 11:23:59 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

static void	config_server_preload(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	uint	f = 1;
	size_t	count = 0;

	init_webserv(webserv);
	if (i < tokens.size() && tokens[i][0] != '{')
	{
		config_error(webserv, "Expected '{' after server keyword.");
	}
	i++;
	while (i < tokens.size() && f != 0)
	{
		if (tokens[i][0] == '{')
			f++;
		if (tokens[i][0] == '}')
			f--;
		if (tokens[i] == "route" && f < 2)
			count++;
		i++;
	}
	if (f != 0)
	{
		config_error(webserv, "Unclosed brackets");
	}
	webserv.routes = new t_route[count];
	if (!webserv.routes)
		exit(EXIT_FAILURE);
	for (i = 0; i < count; i++)
	{
		init_route(webserv.routes[i]);
	}
}

static size_t config_route_parse(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	if (tokens[i + 1][0] != '/')
	{
		config_error(webserv, "Expected route URI after keyword");
	}
	if (tokens[i + 2][0] != '{')
	{
		config_error(webserv, "Expected '{' after route keyword");
	}
	webserv.routes[webserv.routesCount].path = tokens[i + 1];
	i += 2;
	while (tokens[i][0] != '}')
	{
		if (!strchr("{};", tokens[i][0]))
			i = config_route_set(webserv, tokens, i);
		i++;
	}
	webserv.routesCount++;
	return i;
}

static size_t	config_server_parse(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	if (i >= tokens.size())
	{
		config_error(webserv, "Unexpected end of file");
	}
	config_server_preload(webserv, tokens, i + 1);
	i += 2;
	while (tokens[i][0] != '}')
	{
		if (tokens[i] == "route")
		{
			i = config_route_parse(webserv, tokens, i);
		}
		if (!strchr("{};", tokens[i][0]))
		{
			i = config_server_set(webserv, tokens, i);
		}
		i++;
	}
	return i;
}

static void	config_parse_preload(t_config &conf, std::vector<std::string> &tokens)
{
	size_t		i = 0;
	uint		count = 0;
	t_webserv	*webserv = NULL;

	while (i < tokens.size())
	{
		if (tokens[i] == "server")
		{
			count++;
		}
		i++;
	}
	webserv = new t_webserv[count];
	if (!webserv)
	{
		std::cerr << "memory error" << std::endl;
		exit(EXIT_FAILURE);
	}
	conf.serverCount = count;
	conf.webserv = webserv;
}

static void	config_parse(t_config &conf, std::vector<std::string> &tokens)
{
	size_t		i = 0;
	size_t		count = 0;

	config_parse_preload(conf, tokens);
	while (count < conf.serverCount)
	{
		if (tokens[i] == "server")
		{
			i = config_server_parse(conf.webserv[count++], tokens, i);
		}
		i++;
	}
	for(size_t j = 0; j < conf.serverCount; j++)
	{
		std::cout << "server: " << j + 1 << '\n';
		std::cout << "server.port: " << conf.webserv[j].port << '\n';
		std::cout << "server.host: " << conf.webserv[j].host << '\n';
		std::cout << "server.root: " << conf.webserv[j].root << '\n';
		std::cout << "server.errorPage: " << conf.webserv[j].errorPage << '\n';
		std::cout << "server.serverName: " << conf.webserv[j].serverName << '\n';
		std::cout << "server.maxSize: " << conf.webserv[j].maxSize << '\n';
		std::cout << "server.routesCount: " << conf.webserv[j].routesCount << '\n';
		std::cout << std::endl;
	}
}

static std::vector<std::string>	config_lexer(std::ifstream &config)
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
	while (raw[i] != '\0')
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
	}
	return args;
}

void	config(t_config &conf, char *path)
{
	std::ifstream				infile;
	std::vector<std::string>	tokens;

	infile.open(path);
	if (!infile.is_open())
	{
		std::cerr << "Unable to open configuration file" << std::endl;
		exit(EXIT_FAILURE);
	}
	tokens = config_lexer(infile);
	config_parse(conf, tokens);
	infile.close();
}
