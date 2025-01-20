/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:44:49 by diego             #+#    #+#             */
/*   Updated: 2025/01/20 10:52:39 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Route.hpp"

uint	Route::is_method(const std::string &str)
{
	if (str != "GET" && str != "POST")
	{
		return (0);
	}
	return (1);
}

Route::Route(): _path(), _index(), _root(), _redir(), _methods(), _autoindex() {}

Route::~Route() {}

const std::string	&Route::get_path() const
{
	return (this->_path);
}

const std::string	&Route::get_index() const
{
	return (this->_index);
}

const std::string	&Route::get_root() const
{
	return (this->_root);
}

const std::string	&Route::get_redir() const
{
	return (this->_redir);
}

bool	Route::get_autoindex() const
{
	return (this->_autoindex);
}

bool	Route::method_isset(const e_method method) const
{
	return (this->_methods[method]);
}

void	Route::set_path(const std::string &path)
{
	this->_path = path;
}

void	Route::set_root(const std::string &root)
{
	this->_root = root;
}

void	Route::set_index(const std::string &index)
{
	this->_index = index;
}

void	Route::set_redir(const std::string &redir)
{
	this->_redir = redir;
}

void	Route::set_method(const e_method method)
{
	this->_methods[method] = 1;
}

void	Route::set_autoindex(const bool autoindex)
{
	this->_autoindex = autoindex;
}

std::ostream	&operator<<(std::ostream &o, const Route &rhs)
{
	o << "route name: " << rhs.get_path() << '\n';
	o << "route index: " << rhs.get_index() << '\n';
	o << "route root: " << rhs.get_root() << '\n';
	o << "route redir: " << rhs.get_redir() << '\n';
	o << "route autoindex: " << rhs.get_autoindex() << '\n';
	o << "route method GET: " << rhs.method_isset(Route::GET) << '\n';
	o << "route method POST: " << rhs.method_isset(Route::POST) << '\n';
	return (o);
}
