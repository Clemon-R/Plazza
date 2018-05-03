/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** launcher
*/

#include "main.hpp"
#include "main/process/master/master_ui.hpp"
#include "utils/commands/parser.hpp"

void	init_plazza(const int max)
{
	std::unique_ptr<master_ui>	mt = std::make_unique<master_ui>(max);

	mt->set_graphic_mode();
	mt->run();
}