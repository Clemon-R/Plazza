/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** message_handler
*/

#include "main/network/message_handler.hpp"
#include "main/network/messages/command.hpp"
#include "main/network/messages/place.hpp"
#include <sys/socket.h>

std::map<char, std::unique_ptr<imessage>>	message_handler::_messages;

std::map<char, std::unique_ptr<imessage>>	&message_handler::get_messages()
{
	return (_messages);
}

void	message_handler::init_messages()
{
	_messages[1] = std::unique_ptr<imessage>(new message_command());
	_messages[2] = std::unique_ptr<imessage>(new message_place());
}

std::unique_ptr<command>	message_handler::parse_packet(client &client, const char *packet)
{
	char	id = *packet;
	std::map<char, std::unique_ptr<imessage>>::iterator	it = _messages.find(id);
	std::unique_ptr<command>	result;

	if (it != _messages.end())
		return (it->second->decode(client, packet + 1));
	else
		std::cout << "message: packet id unknow\n";
	return (result);
}

void	message_handler::send_packet(client &client, char id, command *com)
{
	std::map<char, std::unique_ptr<imessage>>::iterator	it = _messages.find(id);

	if (it == _messages.end()){
		std::cout << "message: impossible to send packet\n";
		return;
	}
	it->second->encode(client, com);
	if (send(client.get_socket(), it->second->get_buff().c_str(), it->second->get_buff().size(), 0) != -1)
		std::cout << "message: send\n";
	else
		std::cout << "message: failed\n";
}