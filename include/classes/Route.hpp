/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:42:17 by diego             #+#    #+#             */
/*   Updated: 2024/11/15 15:49:09 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ROUTE_H__
# define __ROUTE_H__

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <cstring>

class Route
{
private:
	const uint			_id;
	const std::string	_modifier;
	bool				_autoindex;
	std::string			_root;
	std::string			_index;
	std::string			_return;
	std::string 		_methods[2];

public:
	Route();
	Route(const uint id, const std::string &modifier);
	~Route();

	uint		get_id() const;
	std::string	get_root() const;
	std::string	get_index() const;
	std::string	get_return() const;
	std::string	get_modifier() const;
	bool		get_autoindex() const;
	size_t		set_root(const std::vector<std::string> &args, size_t i);
	size_t		set_index(const std::vector<std::string> &args, size_t i);
	size_t		set_return(const std::vector<std::string> &args, size_t i);
	size_t		set_methods(const std::vector<std::string> &args, size_t i);
	size_t		set_autoindex(const std::vector<std::string> &args, size_t i);

};

std::ostream	&operator<<(std::ostream &o, const Route &rhs);


#endif
