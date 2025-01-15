/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:57:37 by disantam          #+#    #+#             */
/*   Updated: 2025/01/15 20:29:58 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CONFIG_H__
# define __CONFIG_H__

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <cstdlib>
# include <cstring>
# include <stdexcept>
# include "classes/Route.hpp"
# include "classes/Server.hpp"

class	Config
{
private:
	Server						*_servers;
	std::ifstream				_file;
	std::vector<std::string>	_tokens;

	Server	*init_servers(uint i, uint count);
	Route	*init_routes(uint i, uint nServer);

public:
	Config();
	~Config();

	int	declaration_is_closed(uint i);

	int	set_file(const char *path);
	int	read_file();
	int	init();
};

# endif