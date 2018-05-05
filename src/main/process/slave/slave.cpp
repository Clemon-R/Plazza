/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** slave
*/

#include "main/process/slave/slave.hpp"
#include "main/network/message_handler.hpp"
#include "utils/utils.hpp"
#include <unistd.h>
#include <arpa/inet.h>
#include <chrono>
#include <fstream>

slave::slave(unsigned short port, std::size_t max_thread) : _port(port), _socket(-1), _max(max_thread)
	, _protocol(getprotobyname("TCP")), _run(true), _place(max_thread * 2)
{
	std::cout << "slave: process - " << getpid() << std::endl;
	this->run();
}

slave::~slave()
{
	end_run();
	std::cout << "slave: destroyed\n";
}

void	slave::connect_to_server()
{
	std::cout << "slave: trying to connect to server...\n";
	if (!_protocol)
		return;
	_socket = socket(AF_INET, SOCK_STREAM, _protocol->p_proto);
	if (_socket == -1)
		return;
	_config.sin_family = AF_INET;
	_config.sin_port = htons(_port);
	_config.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(_socket, (struct sockaddr *)&_config, sizeof(_config)) == -1){
		std::cout << "slave: impossible to connect to server\n";
		return;
	}
	_client = new client(this, _socket);
	_client_thread = new std::thread([this](){_client->run();});
	std::cout << "slave: successfull connected\n";
	if (_client){
		message_handler::send_packet(*_client, 3, nullptr);
		message_handler::send_packet(*_client, 2, nullptr);
	}
}

void	slave::run()
{
	std::cout << "slave: running...\n";
	connect_to_server();
	dispatch_task();
	end_run();
}

void	slave::dispatch_task()
{
	std::size_t	last = utils::get_seconds();
	std::list<command>::iterator	it;
	std::thread	*list[_max];
	std::thread	**src;
	bool		useless;

	std::cout << "slave: running dispatcher...\n";
	for (int i = 0;i < _max;i++)
		list[i] = nullptr;
	while (utils::get_seconds() - last < 5){
		useless = true;
		_place = _max * 2 - _commands.size();
		it = _commands.begin();
		for (int i = 0;it != _commands.end() && i < _max;i++){
			if (!list[i]){
				useless = false;
				std::cout << "slave: launch command...\n";
				_place--;
				src = &list[i];
				list[i] = new std::thread([it, this, src](){it->run(*_client, src);});
				it = _commands.erase(it);
			}
		}
		if (!useless)
			last = utils::get_seconds();
		else{
			message_handler::send_packet(*_client, 2, nullptr);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	std::cout << "slave: useless\n";
}

void	slave::end_run()
{
	std::cout << "slave: trying to kill...\n";
	_run = false;
	if (_client)
		_client->stop_running();
	if (_socket != -1)
		close(_socket);
	_socket = -1;
	
}

void	slave::set_run(bool value)
{
	_run = value;
}

std::size_t	slave::get_free_place()
{
	return (_place);
}

std::list<command>	&slave::get_commands()
{
	return (_commands);
}

void	slave::add_to_log(command &com)
{
	std::ofstream	file("logs.txt", std::ofstream::out | std::ofstream::app);

	if (!file.is_open())
		return;
	file << "request (" << com.get_file() << ") - " << command::convert_info(com.get_info()) << std::endl;
	file.close();

}