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

	std::cout << "master: trying to create slave\n";
	new std::thread([this](){
		int	process;

		process = fork();
		if (process == 0){
			std::cout << "master: process - " << getpid() << std::endl;
			new slave(_server->get_port(), _max_thread);
		}
		else if (process > 0)
			std::cout << "master: new process has been created\n";
	});
	return (result);
}

bool	master::dispatch_command(command &com)
{
	client	*current = nullptr;
	std::map<int, client *>::iterator	it;

	it = _server->get_clients().begin();
	while (it != _server->get_clients().end()){
		if (it->second->is_running() && it->second->get_place() > 0){
			current = it->second;
			break;
		}
		it++;
	}
	if (current){
		std::cout << "master: dispatch command on file - " << com.get_file() << std::endl;
		message_handler::send_packet(*current, 1, &com);
		current->set_place(current->get_place() + 1);
		return (true);
	}
	return (false);
}

void	master::run_dispatch(std::mutex &lock)
{
	std::list<command>::iterator	it;
	bool	first = true;

	std::cout << "master: dispatching commands...\n";
	do{
		lock.lock();
		it = _commands.begin();
		while (_server && it != _commands.end()){
			if (first)
				create_slave();
			if (dispatch_command(*it))
				it = _commands.erase(it);
			first = false;
		}
		lock.unlock();
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
	std::mutex	lock;
	std::thread	interface([this, &lock](){this->run_interface(lock);});
	std::thread	dispatch([this, &lock](){this->run_dispatch(lock);});

	std::cout << "master: running...\n";
	message_handler::init_messages();
	run_server();
	dispatch.join();
	interface.join();
}