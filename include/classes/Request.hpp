/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:21:27 by disantam          #+#    #+#             */
/*   Updated: 2025/02/26 20:30:00 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __REQUEST_H__
# define __REQUEST_H__

# include <iostream>
# include <string>
# include <stdexcept>
# include <vector>
# include <cstring>
# include <sys/socket.h>
# include <fcntl.h>

class Request
{
private:
	std::string	_method;
	std::string	_url;
	std::string	_protocol;

	std::string	_raw;
	size_t		_len;

	int	parse();
	int	parse_main(uint &i);
	int	set_main(const std::string &tmp);

public:
	Request();
	Request(const std::string &data);
	Request(const Request &request);
	~Request();

	int	receive(const int sock);

	size_t				len() const;
	const std::string	&raw() const;
	const std::string	&protocol() const;
	const std::string	&method() const;
	const std::string	&url() const;

	void	set_url(const std::string &url);
	void	set_method(const std::string &method);
	void	set_protocol(const std::string &protocol);

	Request	&operator=(const Request &rhs);
};

#endif