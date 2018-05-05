/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** command
*/

#include "main/network/messages/connection.hpp"

message_connection::message_connection() : imessage(3)
{
}

void	message_connection::encode(client &client, command *com)
{
	_encode.clear();
	write_char(_id);
}

void	message_connection::decode(client &client, const char *packet)
{
	_decode = packet;
	std::cout << "message: reception of connection\n";
	if (client.get_server())
		client.get_server()->set_creating_slave(false);
}