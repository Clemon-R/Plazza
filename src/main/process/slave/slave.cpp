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

slave::slave(unsigned short port, std::size_t max_thread) : _port(port), _socket(-1), _max(max_thread * 2)
	, _protocol(getprotobyname("TCP")), _run(true)
{
	std::cout << "slave: process - " << getpid() << std::endl;
	this->run();
}

slave::~slave()
{
	_run = false;
	if (_socket != -1)
		close(_socket);
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
	if (_client)
		message_handler::send_packet(*_client, 2, nullptr);
}

void	slave::reception_packet()
{
}

void	slave::run()
{
	bool	_run;

	std::cout << "slave: running...\n";
	connect_to_server();
	dispatch_task();
	end_run();
}

void	slave::dispatch_task()
{
	std::size_t	last = utils::get_seconds();

	while (utils::get_seconds() - last < 60){
	}
}

void	slave::end_run()
{
	delete this;
	std::cout << "slave: trying to kill...\n";
}

void	slave::set_run(bool value)
{
	_run = value;
}

std::size_t	slave::get_free_place()
{
	return (_max);
}