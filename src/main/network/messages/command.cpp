/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** command
*/

#include "main/network/messages/command.hpp"

message_command::message_command() : imessage(1)
{
}

void	message_command::encode(command &com)
{
	_encode.clear();
	write_char(_id);
	write_int(com.get_info());
	write_string(com.get_file());
}

std::unique_ptr<command>	message_command::decode(const char *packet)
{
	std::unique_ptr<command>	result;
	int		info;
	std::string	file;

	_decode = packet;
	info = get_int();
	file = get_string();
	result.reset(new command(file, static_cast<Information>(info)));
	return (result);
}