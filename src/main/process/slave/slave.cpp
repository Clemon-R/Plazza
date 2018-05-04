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
	_client.reset(new client(this, _socket));
	std::cout << "slave: successfull connected\n";
	if (_client)
		message_handler::send_packet(*_client, 2, nullptr);
}

void	slave::reception_packet()
{
	struct pollfd	action;
	char		buff[4097];
	int		len;

	std::cout << "slave: starting reception packet...\n";
	action.fd = _socket;
	action.events = POLLIN;
	action.revents = 0;
	while (this && _run){
		std::cout << "slave: waiting packet...\n";
		while (this && poll(&action, 1, 10) == 0 && _run);
		if (action.revents & POLLIN && _client)
			_client->reception_packet();
		action.revents = 0;
	}
}

void	slave::run()
{
	bool	_run;
	std::thread	reception([this, &_run](){this->reception_packet();});
	std::thread	dispatch([this](){this->dispatch_task();});

	std::cout << "slave: running...\n";
	connect_to_server();
	reception.join();
	dispatch.join();
	end_run();
}

void	slave::dispatch_task()
{
	std::size_t	last = utils::get_seconds();

	while (utils::get_seconds() - last < 60){
	}
	_run = false;
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