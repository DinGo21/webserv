/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:29:21 by disantam          #+#    #+#             */
/*   Updated: 2024/12/20 14:37:11 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

static size_t	config_set_var(std::string *var, std::vector<std::string> &args, size_t i)
{
	i++;
	if (strchr("{};", args[i][0]))
	{
		std::cerr << "Syntax error: " << args[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	*var = args[i];
	return i;
}

static size_t	config_set(t_webserv *webserv, std::vector<std::string> &args, size_t i)
{
	if (!args[i].compare(0, 5, "port"))
	{
		return config_set_var(&webserv->port, args, i);
	}
	else if (!args[i].compare(0, 5, "host"))
	{
		return config_set_var(&webserv->host, args, i);
	}
	else if (!args[i].compare(0, 12, "server_name"))
	{
		return config_set_var(&webserv->serverName, args, i);
	}
	else if (!args[i].compare(0, 9, "max_size"))
	{
		return config_set_var(&webserv->maxSize, args, i);
	}
	else if (!args[i].compare(0, 5, "root"))
	{
		return config_set_var(&webserv->root, args, i);
	}
	else if (!args[i].compare(0, 11, "error_page"))
	{
		return config_set_var(&webserv->errorPage, args, i);
	}
	else if (args[i].compare(0, 6, "route"))
	{
		std::cerr << "Unknown parameter: " << args[i] << std::endl;
		exit(EXIT_FAILURE);
	}
	return i;
}

static void	config_parse(t_webserv *webserv, std::vector<std::string> &args)
{
	size_t	i = 0;

	while (i < args.size() && args[i].compare(0, 7, "server"))
		i++;
	if (!config_check_brackets(args, i + 1))
	{
		std::cerr << "Invalid Syntax" << std::endl;
		exit(EXIT_FAILURE);
	}
	i += 2;
	while (i < args.size() && args[i][0] != '}')
	{
		if (!args[i].compare("route"))
		{
			config_route(webserv, args, i);
		}
		if (!strchr("{};", args[i][0]))
			i = config_set(webserv, args, i);
		i++;
	}
	std::cout << "port: " << webserv->port << "\n";
	std::cout << "host: " << webserv->host << "\n";
	std::cout << "root: " << webserv->root << "\n";
	std::cout << "maxSize: " << webserv->maxSize << "\n";
	std::cout << "serverName: " << webserv->serverName << "\n";
	std::cout << "errorPage: " << webserv->errorPage << std::endl;
}

static std::vector<std::string>	config_get_args(std::ifstream &config)
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

void	config(t_webserv *webserv, char *path)
{
	std::ifstream				infile;
	std::vector<std::string>	args;

	infile.open(path);
	if (!infile.is_open())
	{
		std::cerr << "Unable to open file: " << path << std::endl;
		exit(EXIT_FAILURE);
	}
	args = config_get_args(infile);
	for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	config_parse(webserv, args);
	infile.close();
}
