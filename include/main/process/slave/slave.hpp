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
	#include "main/network/client/client.hpp"

class slave
{
public:
	slave(unsigned short port, std::size_t max_thread);
	~slave();

	void	run();
	void	end_run();

	void	set_run(bool);

	std::size_t	get_free_place();
private:
	void	connect_to_server();
	void	dispatch_task();

	bool	_run;
	std::size_t	_max;
	client	*_client;
	std::thread	*_client_thread;
	unsigned short	_port;
	int		_socket;
	struct protoent	*_protocol;
	struct sockaddr_in	_config;
};
#endif /* !SLAVE_HPP_ */
