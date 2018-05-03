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

class client
{
public:
	client(server &parent, int socket);
	~client();

	const int	get_socket() const noexcept;
	void		reception_packet();
private:
	void		handle_packet(const std::string &packet);

	int	_socket;
	server	&_parent;
};
#endif /* !CLIENT_HPP_ */
