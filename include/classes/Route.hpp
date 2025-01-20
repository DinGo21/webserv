/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:42:17 by diego             #+#    #+#             */
/*   Updated: 2025/01/20 10:14:30 by disantam         ###   ########.fr       */
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

	enum e_method
	{
		GET,
		POST
	};

	static uint	is_method(const std::string &str);

	const std::string	&get_path() const;
	const std::string	&get_index() const;
	const std::string	&get_root() const;
	const std::string	&get_redir() const;
	bool				get_autoindex() const;
	bool				method_isset(const e_method) const;


	void	set_path(const std::string &path);
	void	set_root(const std::string &root);
	void	set_index(const std::string &index);
	void	set_redir(const std::string &redir);
	void	set_method(const e_method method);
	void	set_autoindex(const bool autoindex);
};

std::ostream	&operator<<(std::ostream &o, const Route &rhs);


#endif
