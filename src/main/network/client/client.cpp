/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** client
*/

#include "main/network/client/client.hpp"
#include "main/network/message_handler.hpp"

client::client(server *parent, int socket) : _socket(socket), _parent(parent), _slave(nullptr), _place(0)
{
	std::cout << "client: new server client " << _socket << std::endl;
}

client::client(slave *parent, int socket) : _socket(socket), _parent(nullptr), _slave(parent), _place(0)
{
	std::cout << "client: new slave client " << _socket << std::endl;
}

client::~client()
{
	if (_socket != -1)
		close(_socket);
	std::cout << "client: destroyed\n";
}

void	client::reception_packet()
{
	std::string	packet;
	char		buff[4097];
	int		len;

	std::cout << "client: " << _socket << std::endl;
	std::cout << "client: new packet received\n";
	len = recv(_socket, buff, 4096, 0);
	buff[len] = 0;
	if (len > 0)
		message_handler::parse_packet(*this, buff);
	if (_parent || _slave)
		handle_packet(buff);
}

void	client::handle_packet(const char *packet)
{
	std::map<int, std::unique_ptr<client>>::iterator	it;

	if (*packet)
		return;
	if (_slave != nullptr){
		_slave->set_run(false);
	}
	if (_parent != nullptr){
		it = _parent->get_clients().find(_socket);
		if (it != _parent->get_clients().end())
			_parent->get_clients().erase(it);
	}
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

int	client::get_place()
{
	return (_place);
}