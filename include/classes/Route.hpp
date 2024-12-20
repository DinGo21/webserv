/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:42:17 by diego             #+#    #+#             */
/*   Updated: 2024/12/13 17:14:48 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ROUTE_H__
# define __ROUTE_H__

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <cstring>
# include "Server.hpp"

class Route: public Server
{
protected:
	std::string	_modifier;
	std::string	_return;
	std::string _methods[2];
	bool		_autoindex;

public:
	Route();
	Route(const Route &route);
	virtual ~Route();

	std::string	get_return() const;
	std::string	get_modifier() const;
	bool		get_autoindex() const;
	void		set_return(const std::string &r);
	void		set_autoindex(const bool autoindex);
	void		set_method(const std::string &method);
	void		set_modifier(const std::string &modifier);

	Route		&operator=(const Route &rhs);
};

// std::ostream	&operator<<(std::ostream &o, const Route &rhs);


#endif
