/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:44:49 by diego             #+#    #+#             */
/*   Updated: 2024/11/18 14:18:32 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Route.hpp"

Route::Route(): _id(0), _autoindex(0) {}

Route::Route(const uint id, const std::string &modifier) : _id(id), _modifier(modifier) {}

Route::~Route() {}

// uint	Route::get_id() const
// {
// 	return this->_id;
// }

// std::string	Route::get_modifier() const
// {
// 	return this->_modifier;
// }

// std::string	Route::get_index() const
// {
// 	return this->_index;
// }

// size_t	Route::set_index(const std::vector<std::string> &args, size_t i)
// {
// 	if (i + 1 < args.size() && strchr("{};", args[i + 1][0]))
// 	{
// 		std::cout << "Syntax error: " << args[i + 1] << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	if (i + 2 < args.size() && !strchr(";", args[i + 2][0]))
// 	{
// 		std::cout << "Syntax error: " << args[i + 2] << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	this->_index = args[i + 1];
// 	return i + 2;
// }

// std::string	Route::get_root() const
// {
// 	return this->_root;
// }

// size_t	Route::set_root(const std::vector<std::string> &args, size_t i)
// {
// 	if (i + 1 < args.size() && strchr("{};", args[i + 1][0]))
// 	{
// 		std::cout << "Syntax error: " << args[i + 1] << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	this->_root = args[++i];
// 	return i;
// }

// std::string	Route::get_return() const
// {
// 	return this->_return;
// }

// size_t	Route::set_return(const std::vector<std::string> &args, size_t i)
// {
// 	if (i + 1 < args.size() && strchr("{};", args[i + 1][0]))
// 	{
// 		std::cout << "Syntax error: " << args[i + 1] << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	this->_return = args[++i];
// 	return i;
// }

// size_t	Route::set_methods(const std::vector<std::string> &args, size_t i)
// {
// 	size_t	j = i + 2;
// 	size_t	c = 0;

// 	if (j < args.size() && strchr("{};", args[i + 1][0]))
// 	{
// 		std::cout << "Syntax error: " << args[i + 1] << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	i++;
// 	while (j < args.size() && i < j && !strchr(";", args[i][0]))
// 	{
// 		if (args[i].compare("GET") && args[i].compare("POST"))
// 		{
// 			std::cout << "Unknown method: " << args[i] << std::endl;
// 			exit(EXIT_FAILURE);
// 		}
// 		this->_methods[c++] = args[i++];
// 	}
// 	return i;
// }

// bool	Route::get_autoindex() const
// {
// 	return this->_autoindex;
// }

// size_t	Route::set_autoindex(const std::vector<std::string> &args, size_t i)
// {
// 	if (i + 1 < args.size() && strchr("{};", args[i + 1][0]) &&
// 		args[i + 1].compare("ON") && args[i + 1].compare("OFF"))
// 	{
// 		std::cout << "Syntax error: " << args[i + 1] << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	this->_autoindex = 0;
// 	if (!args[i + 1].compare("ON"))
// 	{
// 		this->_autoindex = 1;
// 	}
// 	return i + 2;
// }

// std::ostream    &operator<<(std::ostream &o, const Route &rhs)
// {
// 	o << "Route=" << '\n';
// 	o << "id: " << rhs.get_id() << '\n';
// 	o << "modifier: " << rhs.get_modifier() << '\n';
// 	o << "index: " << rhs.get_index() << '\n';
// 	o << "root: " << rhs.get_root() << '\n';
// 	o << "return: " << rhs.get_return() << '\n';
// 	o << "autoindex: " << rhs.get_autoindex() << '\n';

// 	return o;
// }
