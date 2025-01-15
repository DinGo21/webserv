/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:42:17 by diego             #+#    #+#             */
/*   Updated: 2025/01/15 14:50:59 by disantam         ###   ########.fr       */
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
protected:
	std::string	_path;
	std::string	_index;
	std::string	_root;
	std::string	_redir;
	bool		_methods[2];
	bool		_autoindex;

public:
	Route();
	~Route();

};

// std::ostream	&operator<<(std::ostream &o, const Route &rhs);


#endif
