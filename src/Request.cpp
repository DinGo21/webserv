/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:27:40 by disantam          #+#    #+#             */
/*   Updated: 2025/02/14 16:17:01 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Request.hpp"

Request::Request()
{
	this->_len = 0;
}

Request::Request(const std::string &data)
{
	int	i = 0;
	int	j = 0;

	this->_raw = data;
	this->_len = data.size();
	while (this->_raw[i] != '\n' && this->_raw[i] != '\0')
	{
		while (this->_raw[i] == ' ')
			i++;
		j = this->_raw.find_first_of(" \n", i);
		if (!this->_raw.compare(i, 3, "GET") || !this->_raw.compare(i, 4, "POST") ||
			!this->_raw.compare(i, 6, "DELETE"))
		{
			this->_method = this->_raw.substr(i, j - i);
		}
		if (!this->_raw.compare(i, 1, "/"))
		{
			this->_url = this->_raw.substr(i, j - i);
		}
		if (!this->_raw.compare(i, 4, "HTTP"))
		{
			this->_protocol = this->_raw.substr(i, j - i);
		}
		i = j;
		i++;
	}
	std::cout << this->_method << '\n';
	std::cout << this->_url << '\n';
	std::cout << this->_protocol << '\n';
}

Request::~Request() {}

Request::Request(const Request &request)
{
	*this = request;
}

size_t	Request::len() const
{
	return (this->_len);
}

const std::string	&Request::raw() const
{
	return (this->_raw);
}

const std::string	&Request::protocol() const
{
	return (this->_protocol);
}

const std::string	&Request::method() const
{
	return (this->_method);
}

const std::string	&Request::url() const
{
	return (this->_url);
}

Request	&Request::operator=(const Request &rhs)
{
	this->_len = rhs.len();
	this->_raw = rhs.raw();
	this->_url = rhs.url();
	this->_protocol = rhs.protocol();
	this->_method = rhs.method();
	return (*this);
}
