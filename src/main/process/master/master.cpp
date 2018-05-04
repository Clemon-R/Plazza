/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master
*/

#include "main/process/master/master.hpp"
#include "main/network/message_handler.hpp"

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

	bg.reset(new std::thread([this](){
		int	process;

		process = fork();
		if (process == 0){
			std::cout << "master: process - " << getpid() << std::endl;
			new slave(_server->get_port());
		}
		else if (process > 0)
			std::cout << "master: new process has been created\n";
	}));
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
	if (_server)
		_server->stop();
	std::cout << "master: end of running\n";
}

void	master::run_server()
{
	std::cout << "master: starting server...\n";
	_server.reset(new server());
	if (_server)
		_server->run();
}

void	master::run()
{
	std::thread	interface([this](){this->run_interface();});
	std::thread	dispatch([this](){this->run_dispatch();});
	std::thread	server([this](){this->run_server();});

	std::cout << "master: running...\n";
	message_handler::init_messages();
	server.join();
	interface.join();
	dispatch.join();
}