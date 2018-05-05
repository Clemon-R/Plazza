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

void	message_command::encode(client &client, command *com)
{
	_encode.clear();
	write_char(_id);
	if (!com)
		return;
	write_int(com->get_info());
	write_string(com->get_file());
	write_string(com->get_response());
}

void	message_command::decode(client &client, const char *packet)
{
	int		info;
	std::string	file;
	std::string	response;
	command		com;

	_decode = packet;
	info = get_int();
	file = get_string();
	response = get_string();
	std::cout << "message: command received on file " << file << std::endl;
	com = command(file, static_cast<Information>(info));
	std::cout << "message: command response - " << response << std::endl;
	com.set_response(response);
	if (client.get_slave()){
		client.get_slave()->get_commands().push_back(com);
		client.get_slave()->add_to_log(com);
	}
	else{
		client.get_server()->get_responses().push_back(com);
		client.get_server()->add_to_log(com);
	}
}

