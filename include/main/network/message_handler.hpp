/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** message_handler
*/

#ifndef MESSAGE_HANDLER_HPP_
	#define MESSAGE_HANDLER_HPP_

	#include <map>
	#include <functional>
	#include <iostream>
	#include <memory>
	#include "main/network/imessage.hpp"
	#include "main/network/client/client.hpp"

class message_handler
{
public:
	static std::unique_ptr<command>	parse_packet(client &client, const char *packet);
	static void	send_packet(client &client, char id, command *com);

	static std::map<char, std::unique_ptr<imessage>>	&get_messages();
	static void	init_messages();
private:
	static std::map<char, std::unique_ptr<imessage>>	_messages;
};
#endif /* !MESSAGE_HANDLER_HPP_ */
