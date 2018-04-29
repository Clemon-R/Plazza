/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** parser
*/

#ifndef PARSER_HPP_
	#define PARSER_HPP_

	#include "utils/commands/command.hpp"

class commandParser
{
public:
	static command	&parse_line(const std::string &line);
};
#endif /* !PARSER_HPP_ */
