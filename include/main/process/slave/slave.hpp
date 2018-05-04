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
	#include <list>
	#include "utils/commands/command.hpp"

class slave
{
public:
	slave(unsigned short port);
	~slave();

	void	run();
	void	end_run();
private:
	void	connect_to_server();
	void	reception_packet();
	void	handle_packet(const char *packet);
	void	dispatch_task();

	bool	_run;
	unsigned short	_port;
	int		_socket;
	struct protoent	*_protocol;
	struct sockaddr_in	_config;
};
#endif /* !SLAVE_HPP_ */
