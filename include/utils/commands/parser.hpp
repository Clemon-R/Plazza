/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** parser
*/

#ifndef PARSER_HPP_
	#define PARSER_HPP_

	#include "utils/commands/command.hpp"
	#include <list>
	#include <map>
	#include <istream>
	#include <iostream>

class commandParser
{
public:
	static std::list<command>	parse_line(std::string &line);
	static std::list<command>	parse_file(std::istream &);
private:
	static Information	get_action(const std::string &);

	static std::map<std::string, Information>	_list;
};
#endif /* !PARSER_HPP_ */
