/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** command
*/

#ifndef MCONNECTION_HPP_
	#define MCONNECTION_HPP_

class command;
	#include "main/network/imessage.hpp"

class message_connection : public imessage
{
public:
	message_connection();

	void	encode(client &client, command *com) override final;
	void	decode(client &client, const char *) override final;
};
#endif /* !COMMAND_HPP_ */
