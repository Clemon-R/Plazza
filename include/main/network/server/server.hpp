/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** server
*/

#ifndef SERVER_HPP_
	#define SERVER_HPP_

	#include <iostream>
	#include <memory>
	#include <list>
	#include <map>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <poll.h>
	#include <unistd.h>
	#include <thread>
class client;
	#include "main/network/client/client.hpp"

class server
{
public:
	server();
	~server();

	void	run();
	void	stop();

	std::map<int, client *>	&get_clients();
	void	set_clients(std::map<int, client *> &);
	unsigned short	get_port() const noexcept;
private:
	void	handle_client();

	struct protoent	*_protocol;
	int		_socket;
	unsigned short	_port;
	struct sockaddr_in	_config;

	bool		_run;
	std::map<int, client *>	_clients;
	std::map<int, std::thread *>	_clients_thread;
};
#endif /* !SERVER_HPP_ */
