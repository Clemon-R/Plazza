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

std::pair<std::unique_ptr<std::thread>, std::unique_ptr<slave>>	master::create_slave()
{
	std::pair<std::unique_ptr<std::thread>, std::unique_ptr<slave>>	result;
	std::unique_ptr<std::thread>	bg;
	std::unique_ptr<slave>		sl;

	bg.reset(new std::thread([&sl](){sl.reset(new slave());}));
	bg->join();
	return (result);
}

void	master::run_dispatch()
{
	std::list<command>::iterator	it;
	std::cout << "master: dispatching commands...\n";

	do{
		it = _commands.begin();
		while (it != _commands.end()){
			create_slave();
			it = _commands.erase(it);
		}
	} while (_run || _commands.size() > 0);
	std::cout << "master: end of running\n";
}

void	master::run()
{
	std::thread	interface([this](){this->run_interface();});
	std::thread	dispatch([this](){this->run_dispatch();});

	std::cout << "master: running...\n";
	interface.join();
	dispatch.join();
}