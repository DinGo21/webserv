/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:29:21 by disantam          #+#    #+#             */
/*   Updated: 2025/01/03 14:09:25 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

static void	config_parse_prerun(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	uint	f = 1;
	size_t	count = 0;
	
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
		if (!tokens[i].compare(0, 6, "route") && f < 2)
		{
			count++;
		}
		i++;
	}
	if (f != 0)
	{
		config_error(webserv, "Unclosed brackets");
	}
	webserv.routes = new t_route[count];
	if (!webserv.routes)
		exit(EXIT_FAILURE);
}

static void config_route_parse(t_webserv &webserv, std::vector<std::string> &tokens, size_t i)
{
	if (tokens[i + 1][0] != '/' || tokens[i + 2][0] != '{')
	{
		config_error(webserv, "Syntax Error");
	}
	webserv.routes[webserv.routesCount].path = tokens[i + 1];
	i += 2;
	while (tokens[i][0] != '}')
	{
		if (!strchr("{};", tokens[i][0]))
			i = config_route_set(webserv, tokens, i);
	}

}

static void	config_server_parse(t_webserv &webserv, std::vector<std::string> &tokens)
{
	size_t	i = 0;

	while (i < tokens.size() && tokens[i].compare(0, 7, "server"))
		i++;
	if (i >= tokens.size())
	{
		config_error(webserv, "Unexpected end of file");
	}
	config_parse_prerun(webserv, tokens, i + 1);
	i += 2;
	while (tokens[i][0] != '}')
	{
		if (!tokens[i].compare(0, 6, "route"))
		{
			config_route_parse(webserv, tokens, i);
		}
		if (!strchr("{};", tokens[i][0]))
			i = config_server_set(webserv, tokens, i);
		i++;
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

void	config(t_webserv &webserv, char *path)
{
	std::ifstream				infile;
	std::vector<std::string>	tokens;

	infile.open(path);
	if (!infile.is_open())
	{
		config_error(webserv, "Unable to open configuration file");
	}
	tokens = config_lexer(infile);
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end() - 1; it++)
	{
		std::cout << *it << '\n';
	}
	std::cout << std::endl;
	config_server_parse(webserv, tokens);
	std::cout << "port: " << webserv.port << "\n";
	std::cout << "host: " << webserv.host << "\n";
	std::cout << "root: " << webserv.root << "\n";
	std::cout << "maxSize: " << webserv.maxSize << "\n";
	std::cout << "serverName: " << webserv.serverName << "\n";
	std::cout << "errorPage: " << webserv.errorPage << std::endl;
	infile.close();
}
