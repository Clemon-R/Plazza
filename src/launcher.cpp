/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** launcher
*/

#include "main.hpp"
#include "main/process/master/master_none.hpp"
#include "utils/commands/parser.hpp"

void	init_plazza(const int max)
{
	std::unique_ptr<master_none>	mt = std::make_unique<master_none>(max);

	mt->run();
}