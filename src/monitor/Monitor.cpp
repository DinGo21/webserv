/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monitor.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:11:15 by disantam          #+#    #+#             */
/*   Updated: 2025/04/01 16:31:57 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Monitor.hpp"

Monitor::Monitor() {}

Monitor::~Monitor() {}

Monitor::Monitor(Server *servers)
{
	listen_t	listenSock;

	this->_servers = servers;
	for (uint i = 0; i < Server::get_nServers(); i++)
	{
		if (servers[i].isdefault())
		{
			memset(&listenSock, 0, sizeof(listenSock));
			listenSock.addr.sin_family = AF_INET;
			listenSock.addr.sin_port = htons(atoi(servers[i].get_port().c_str()));
			listenSock.addr.sin_addr.s_addr = htonl(INADDR_ANY);
			listenSock.addrlen = sizeof(listenSock.addr);
			this->_listenSocks.push_back(listenSock);
		}
	}
}

int	Monitor::run()
{
	this->sockets_set();
	while (true)
	{
		memcpy(&this->_workingSet, &this->_masterSet, sizeof(this->_masterSet));
		this->_timeout.tv_sec = 1 * 60;
		this->_timeout.tv_usec = 0;
		this->_socksReady = select(this->_maxSock + 1, &this->_workingSet,
			NULL, NULL, &this->_timeout);
		if (this->_socksReady < 0)
		{
			std::cerr << strerror(errno) << std::endl;
			break;
		}
		if (this->_socksReady == 0)
			break;
		if (this->register_event() < 0)
			break;
	}
	this->sockets_clean();
	return (0);
}
