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

	void	encode(command &com) override final;
	std::unique_ptr<command>	decode(const char *) override final;
};
#endif /* !COMMAND_HPP_ */
