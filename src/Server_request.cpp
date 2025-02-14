/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:31:54 by disantam          #+#    #+#             */
/*   Updated: 2025/02/14 16:48:35 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Server.hpp"

void	Server::response_make(const Request &request, std::string &response)
{
	std::string		body;
	std::string		tmp;
	std::ifstream	file;

	response = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
	if (request.url() == "/")
		file.open("index.html");
	else
		file.open(request.url().c_str());
	if (!file.is_open())
	{
		std::cerr << request.url() << " not found" << std::endl;
		response += "0\n\n";
		return;
	}
	while (std::getline(file, tmp))
	{
		body += tmp;
		body.push_back('\n');
	}
	response += this->get_maxSize();
	response.push_back('\n');
	response.push_back('\n');
	response += body;
}

int	Server::request_check(const Request &request)
{
	
}

Request	Server::request_read(int sock)
{
	int 		nb = 1;
	char		buff[501];
	std::string	raw;

	while (nb != 0)
	{
		nb = recv(sock, buff, 500, MSG_DONTWAIT);
		if (nb < 0)
		{
			break;
		}
		buff[nb] = '\0';
		raw += buff;
	}
	std::cout << raw;
	return (raw);
}
