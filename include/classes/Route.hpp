/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:42:17 by diego             #+#    #+#             */
/*   Updated: 2024/10/30 11:28:30 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ROUTE_H__
# define __ROUTE_H__

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>

class Route
{
private:
	const uint			_id;
	const std::string	_modifier;
	std::string			_root;
	std::string			_index;
	std::string			_return;
	std::string 		_methods[2];
	bool				_autoindex;

public:
	Route();
	Route(const uint id, const std::string &modifier);
	~Route();
	
};

#endif
