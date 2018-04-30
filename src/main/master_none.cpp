/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master_none
*/

#include "main/master.hpp"
#include "main/master_none.hpp"
#include "utils/commands/parser.hpp"

master_none::master_none(const int max) : master(max)
{
}

static bool	compare_commands(const command &first, const command &second)
{
	return (true);
}

void	master_none::run_interface()
{
	std::cout << "master: run interface without graphic...\n";
	while (_run){
		std::cout << " > ";
		_commands.merge(commandParser::parse_file(stdin), compare_commands);
	}
}