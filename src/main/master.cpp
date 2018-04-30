/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master
*/

#include "main/master.hpp"

master::master(const int max_thread) : _max_thread(max_thread), _graphic_mode(false), _run(true)
{
	std::cout << "master: running init...\n";
	std::cout << "master: max thread - " << max_thread << std::endl;
}

master::~master()
{	
	std::cout << "master: closing...\n";
}

void	master::set_commands(const std::list<command> &value)
{
	std::cout << "master: new list of commands\n";
	_commands = value;
}

void	master::set_graphic_mode() noexcept
{
	_graphic_mode = true;
}

void	master::run_dispatch()
{
	std::cout << "master: dispatching commands...\n";
}

void	master::run()
{
	std::thread	dispatch([this](){this->run_dispatch();});

	std::cout << "master: running...\n";
	dispatch.join();
	run_interface();
}