/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** command
*/

#include "main/network/messages/place.hpp"

message_place::message_place() : imessage(2)
{
}

void	message_place::encode(client &client, command *com)
{
	_encode.clear();
	write_char(_id);
	if (!client.get_slave())
		return;
	write_int(client.get_slave()->get_free_place());
}

void	message_place::decode(client &client, const char *packet)
{
	_decode = packet;
	client.set_place(get_int());
	std::cout << "message: reception of " << client.get_place() << " place(s)\n";
}