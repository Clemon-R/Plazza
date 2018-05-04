/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** command
*/

#ifndef MPLACE_HPP_
	#define MPLACE_HPP_

class command;
	#include "main/network/imessage.hpp"

class message_place : public imessage
{
public:
	message_place();

	void	encode(client &client, command *com) override final;
	std::unique_ptr<command>	decode(client &client, const char *) override final;
};
#endif /* !COMMAND_HPP_ */
