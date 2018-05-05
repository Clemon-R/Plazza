/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** client
*/

#include "main/network/client/client.hpp"
#include "main/network/message_handler.hpp"
#include <thread>
#include <poll.h>

client::client(server *parent, int socket) : _socket(socket), _parent(parent), _slave(nullptr), _place(0), _run(true)
{
	std::cout << "client: new server client " << _socket << std::endl;

}

client::client(slave *parent, int socket) : _socket(socket), _parent(nullptr), _slave(parent), _place(0), _run(true)
{
	std::cout << "client: new slave client " << _socket << std::endl;

}

client::~client()
{
	stop_running();
	std::cout << "client: destroyed\n";
}

void	client::run()
{
	struct pollfd	action;

	std::cout << "client: running - " << (_slave ? "(slave)" : _parent ? "(server)" : "broken")<< _socket << std::endl;
	action.fd = _socket;
	action.events = POLLIN;
	action.revents = 0;
	while (_run){
		while (poll(&action, 1, 0) == 0 && _run);
		std::cout << "client: action\n";
		reception_packet();
	}
	std::cout << "client: stop running\n";
}

void	client::reception_packet()
{
	std::string	packet;
	char		buff[4097];
	int		len;

	std::cout << "client: new packet received\n";
	len = recv(_socket, buff, 4096, 0);
	buff[len] = 0;
	std::cout << "client: size of the packet - " << len << std::endl;
	if (len == -1)
		return;
	if (len > 0 && _run)
		message_handler::parse_packet(*this, buff, len);
	if (len == 0 && (_parent || _slave))
		stop_running();
}

const int	client::get_socket() const noexcept
{
	return (_socket);
}

server		*client::get_server() const noexcept
{
	return (_parent);
}

slave		*client::get_slave() const noexcept
{
	return (_slave);
}

void	client::set_place(int value)
{
	_place = value;
}

int	client::get_place() const noexcept
{
	return (_place);
}

bool	client::is_running()
{
	return (_run);
}

void	client::stop_running()
{
	std::map<int, client *>::iterator	it;

	_run = false;
	if (_parent != nullptr){
		it = _parent->get_clients().find(_socket);
		if (it != _parent->get_clients().end()){
			std::cout << "client: remove from the server\n";
			_parent->get_clients().erase(it);
		}
	}
	if (_socket != -1)
		close(_socket);
	_socket = -1;
}