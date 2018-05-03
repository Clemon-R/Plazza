/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** slave
*/

#ifndef SLAVE_HPP_
	#define SLAVE_HPP_

	#include <thread>
	#include <memory>
	#include <iostream>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <poll.h>

class slave
{
public:
	slave(unsigned short port);
	~slave();

	void	run();
	void	end_run();
private:
	void	connect_to_server();

	int	_parent;
	unsigned short	_port;
	int		_socket;
	struct protoent	*_protocol;
	struct sockaddr_in	_config;
};
#endif /* !SLAVE_HPP_ */
