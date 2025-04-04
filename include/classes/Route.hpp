/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:42:17 by diego             #+#    #+#             */
/*   Updated: 2025/02/27 12:54:05 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ROUTE_H__
# define __ROUTE_H__

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <cstring>

enum e_method
{
	GET,
	POST,
	DELETE
};

class Route
{
private:
	std::string	_path;
	std::string	_index;
	std::string	_root;
	std::string	_redir;
	bool		_methods[3];
	bool		_autoindex;

public:
	Route();
	~Route();

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
