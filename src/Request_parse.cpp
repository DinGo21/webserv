/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_parse.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:48:20 by disantam          #+#    #+#             */
/*   Updated: 2025/02/26 21:05:55 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Request.hpp"

int	Request::parse_main(uint &i)
{
	uint		j = 0;
	std::string	tmp;

	while (this->_raw[i] != '\0' && this->_raw[i] != '\r')
	{
		while (this->_raw[i] == ' ')
			i++;
		if (strchr("\r\n", this->_raw[i]) || this->_raw[i] == '\0')
			break;
		j = this->_raw.find_first_of(" \r\n", i);
		tmp = this->_raw.substr(i, j - i);
		if (this->set_main(tmp) < 0)
			return (-1);
		i = j;
	}
	if (this->_method.size() == 0 || this->_url.size() == 0 ||
		this->_protocol.size() == 0)
	{
		std::cerr << "Missing request elements" << std::endl;
		return (-1);
	}
	return (0);
}

int	Request::parse()
{
	uint	i = 0;

	if (this->parse_main(i) < 0)
	{
		return (-1);
	}
	return (0);
}
