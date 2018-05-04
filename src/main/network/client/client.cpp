/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** client
*/

#include "main/network/client/client.hpp"
#include "main/network/message_handler.hpp"

client::client(server &parent, int socket) : _socket(socket), _parent(parent)
{
	std::cout << "client: new client\n";
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
	do{
		len = read(_socket, buff, 4096);
		buff[len] = 0;
		packet.append(std::string(buff));
	} while (len == 4096);
	handle_packet(packet);
}

void	client::handle_packet(const std::string &packet)
{
	std::map<int, std::unique_ptr<client>>::iterator	it = _parent.get_clients().find(_socket);

	if (packet.empty()){
		if (it != _parent.get_clients().end())
			_parent.get_clients().erase(it);
		return;
	}
}

const int	client::get_socket() const noexcept
{
	return (_socket);
}