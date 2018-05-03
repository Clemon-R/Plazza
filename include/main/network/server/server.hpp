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
class client;
	#include "main/network/client/client.hpp"

class server
{
public:
	server();
	~server();

	void	run();
	void	stop();

	std::map<int, std::unique_ptr<client>>	&get_clients();
	unsigned short	get_port() const noexcept;
private:
	void	pack_all_socket(struct pollfd **);

	bool	handle_action(struct pollfd *, std::size_t);
	void	handle_client();

	struct protoent	*_protocol;
	int		_socket;
	unsigned short	_port;
	struct sockaddr_in	_config;

	bool		_run;
	std::map<int, std::unique_ptr<client>>	_clients;
};
#endif /* !SERVER_HPP_ */
