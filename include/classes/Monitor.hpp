/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monitor.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:53:22 by disantam          #+#    #+#             */
/*   Updated: 2025/04/01 16:30:46 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MONITOR_H__
# define __MONITOR_H__

# include <iostream>
# include <fstream>
# include <string>
# include <list>
# include <stdexcept>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include "classes/Server.hpp"

typedef struct listen_s
{
	int					sockd;
	struct sockaddr_in	addr;
	socklen_t			addrlen;
}						listen_t;

class Monitor
{
private:
	Server				*_servers;
	std::list<listen_t>	_listenSocks;
	int					_socksReady;
	int					_maxSock;
	fd_set				_masterSet;
	fd_set				_workingSet;
	struct timeval		_timeout;
	
	void	sockets_set();
	void	sockets_clean();
	void	sockets_close(const int sock);
	bool	sockets_islistening(const int sockd);
	int		register_event();
	int		register_connection(const int ListenSock);
	int		register_request(const int sock, int &flag);

public:
	Monitor();
	Monitor(Server *servers);
	~Monitor();

	int		sockets_init();
	int		run();
};

#endif