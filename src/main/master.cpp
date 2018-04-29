/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master
*/

#include "master.hpp"

master::master(const int max_thread)
{
	std::cout << "master: running init...\n";
}

master::~master()
{	
	std::cout << "master: closing...\n";
}

bool	master::init_graphic()
{
	std::cout << "master: graphic needed\nmaster: running init...\n";
	_graphic.reset(nullptr);
}