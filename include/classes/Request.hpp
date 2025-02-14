/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:21:27 by disantam          #+#    #+#             */
/*   Updated: 2025/02/14 13:39:40 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __REQUEST_H__
# define __REQUEST_H__

# include <iostream>
# include <string>
# include <vector>

class Request
{
private:
	std::string	_method;
	std::string	_url;
	std::string	_protocol;

	std::string	_raw;
	size_t		_len;
public:
	Request();
	Request(const std::string &data);
	Request(const Request &request);
	~Request();

	size_t				len() const;
	const std::string	&raw() const;
	const std::string	&protocol() const;
	const std::string	&method() const;
	const std::string	&url() const;

	Request	&operator=(const Request &rhs);
};

#endif