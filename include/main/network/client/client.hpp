/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** client
*/

#ifndef CLIENT_HPP_
	#define CLIENT_HPP_

	#include <iostream>
	#include <unistd.h>

class server;
	#include "main/network/server/server.hpp"

class slave;
	#include "main/process/slave/slave.hpp"

class client
{
public:
	client(slave *parent, int socket);
	client(server *parent, int socket);
	~client();

	const int	get_socket() const noexcept;
	server	*get_server() const noexcept;
	slave	*get_slave() const noexcept;
	void		reception_packet();
	void	set_place(int);
	int	get_place();
private:
	void		handle_packet(const char *packet);

	int	_socket;
	server	*_parent;
	slave	*_slave;

	int	_place;
};
#endif /* !CLIENT_HPP_ */
