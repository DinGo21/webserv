/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:27:40 by disantam          #+#    #+#             */
/*   Updated: 2025/02/26 20:52:25 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "classes/Request.hpp"

Request::Request()
{
	this->_len = 0;
}

Request::Request(const std::string &data)
{
	(void)data;
}

Request::~Request() {}

Request::Request(const Request &request)
{
	*this = request;
}

int	Request::receive(const int sock)
{
	int 		nb = 1;
	char		buff[501];
	std::string	req;

	while (nb != 0)
	{
		nb = recv(sock, buff, 500, MSG_DONTWAIT);
		if (nb < 0)
		{
			break;
		}
		buff[nb] = '\0';
		req += buff;
	}
	this->_raw = req;
	std::cout << this->_raw;
	if (this->parse() < 0)
	{
		return (-1);
	}
	return (0);
}

int	Request::set_main(const std::string &tmp)
{
	try
	{
		if (is_method(tmp))
		{
			this->set_method(tmp);
		}
		else if (tmp[0] == '/')
		{
			this->set_url(tmp);
		}
		else if (!tmp.compare(0, 5,"HTTP/"))
		{
			this->set_protocol(tmp);
		}
		else
		{
			std::cerr << "Invalid request element: " << tmp << std::endl;
			return (-1);
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	return (0);
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

void	Request::set_method(const std::string &method)
{
	this->_method = method;
}

void	Request::set_url(const std::string &url)
{
	this->_url = url;
}

void	Request::set_protocol(const std::string &protocol)
{
	this->_protocol = protocol;
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
