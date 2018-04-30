/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master_ui
*/

#include "main/master.hpp"
#include "main/master_ui.hpp"

master_ui::master_ui(const int max) : master(max)
{

}

bool	master_ui::init_graphic()
{
	if (!_graphic_mode)
		return (false);
	std::cout << "master: graphic needed\nmaster: running init...\n";
	_graphic.reset(nullptr);
	return (true);
}

void	master_ui::run_interface()
{
	
}