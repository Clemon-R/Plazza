/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** launcher
*/

#include "main.hpp"
#include "main/master_ui.hpp"
#include "utils/commands/parser.hpp"

void	init_plazza(const int max)
{
	std::unique_ptr<master_ui>	mt = std::make_unique<master_ui>(max);
	std::list<command>	list = commandParser::parse_file(stdin);

	mt->set_commands(list);
	mt->set_graphic_mode();
	mt->run();
}