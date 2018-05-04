/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** command
*/

#ifndef MCOMMAND_HPP_
	#define MCOMMAND_HPP_

class command;
	#include "main/network/imessage.hpp"

class message_command : public imessage
{
public:
	message_command();

	void	encode(client &client, command *com) override final;
	std::unique_ptr<command>	decode(client &client, const char *) override final;
};
#endif /* !COMMAND_HPP_ */
