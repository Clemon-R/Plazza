/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master_none
*/

#include "main/process/master/master.hpp"
#include "main/process/master/master_none.hpp"
#include "utils/commands/parser.hpp"
#include <iostream>

master_none::master_none(const int max) : master(max)
{
}

static bool	compare_commands(const command &first, const command &second)
{
	return (true);
}

void	master_none::run_interface(std::mutex &lock)
{
	std::string	line;
	std::list<command>	list;

	std::cout << "master: run interface without graphic...\n";
	std::cout << "***Enter your commands***\n";
	while (std::getline(std::cin, line)){
		if (line.empty()){
			std::cout << "\n";
			break;
		}
		lock.lock();
		list = _commands;
		for (const auto &elem : commandParser::parse_line(line))
			list.push_back(elem);
		_commands = list;
		lock.unlock();
		std::cout << "***Enter your commands***\n";
	}
	std::cout << "master: end of line\n";
	_run = false;
}