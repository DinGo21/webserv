/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:30:37 by disantam          #+#    #+#             */
/*   Updated: 2024/10/11 17:01:11 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#define PORT 8080

std::string	make_response(std::string buff, int sock)
{
	std::ifstream	infile;
	std::string		resp, body, line;
	int				i;

	i = buff.find('/', 0) + 1;
	std::cout << buff.substr(i, buff.find_first_of(" \n", i) - i) << std::endl;
	infile.open(buff.substr(i, buff.find_first_of(" \n", i) - i));
	if (!infile.is_open())
	{
		return (resp = "HTTP/1.1 404 Not Found\nContent-Type: text/plain\nContent-Length: 0\n\n");
	}
	while (std::getline(infile, line))
	{
		body += line;
		body.push_back('\n');
	}
	resp += "HTTP/1.1 200 OK\n";
	resp += "Content-Type: text/html\n";
	resp += "Content-length: 145\n\n";
	infile.close();
	return (resp + body);
}

int	init_server(int server_fd, struct sockaddr_in &address, int addrlen)
{
	int			new_socket, nb;
	char 		buff[10000];
	std::string	resp;

	std::cout << "+++Waiting new connection+++" << std::endl;
	new_socket = accept(server_fd, (struct sockaddr *)&address, 
				(socklen_t *)&addrlen);
	if (new_socket < 0)
	{
		std::cerr << "Cannot accept connection. errno: " << errno << std::endl;
		return 1;
	}
	nb = read(new_socket, buff, 10000);
	std::cout << buff << std::endl;
	resp = make_response(buff, new_socket);
	std::cout << resp;
	write(new_socket, resp.c_str(), resp.size());
	std::cout << "---Hello message sent---" << std::endl;
	close(new_socket);
	return 0;
}

int main(int argc, char **argv)
{
	int					server_fd, addrlen, reuseaddr;
	struct sockaddr_in	address;

	addrlen = sizeof(address);
	memset(&address, 0, addrlen);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);
	reuseaddr = 1;
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		std::cerr << "Cannot create socket. errno: " << errno << std::endl;
		return 1;
	}
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
				sizeof(reuseaddr));
	if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0)
	{
		std::cerr << "Failed to bind port " << PORT << ". errno: " << errno << std::endl;
		return 1;
	}
	if (listen(server_fd, 10) < 0)
	{
		std::cerr << "Failed to listen on socket. errno: " << errno << std::endl;
		return 1;
	}
	return init_server(server_fd, address, addrlen);
}
