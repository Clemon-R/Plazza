/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** server
*/

#include "main/network/server/server.hpp"
#include <fstream>
#include <stdio.h>

server::server() : _protocol(getprotobyname("TCP")), _socket(-1), _run(true), _port(0)
{
	char	option = 1;
	socklen_t addrlen = sizeof(_config);

	std::cout << "server: creating server...\n";
	remove("logs.txt");
	if (!_protocol)
		return;
	_socket = socket(AF_INET, SOCK_STREAM, _protocol->p_proto);
	if (_socket == -1)
		return;
	_config.sin_family = AF_INET;
	_config.sin_port = htons(_port);
	_config.sin_addr.s_addr = INADDR_ANY;
	if (bind(_socket, (struct sockaddr *)&_config, sizeof(_config)) == -1)
		return;
	if(getsockname(_socket, (struct sockaddr *)&_config, &addrlen) != -1) 
		_port = static_cast<uint16_t >(ntohs(_config.sin_port));
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&option, sizeof(option));
	std::cout << "server: random port is " << _port << std::endl;
	std::cout << "server: created\n";
}

server::~server()
{
	std::cout << "server: destroyed\n";
}

void	server::handle_client()
{
	int	client_fd = 0;
	struct sockaddr_in	s_client_in;
	socklen_t		s_client_size = sizeof(s_client_in);
	client	*current;

	std::cout << "server: action on server\n";
	client_fd = accept(_socket, (struct sockaddr *)&s_client_in, &s_client_size);
	if (client_fd == -1)
		return;
	_clients.insert(std::pair<int, client *>(client_fd, new client(this, client_fd)));
	_clients_thread.insert(std::pair<int, std::thread *>(client_fd, new std::thread([this, client_fd](){
		std::map<int, client *>::iterator	it = _clients
		.find(client_fd);

		if (it != _clients.end())
			it->second->run();
	})));
}

void	server::run()
{
	struct pollfd	action;
	int	fd;

	std::cout << "server: starting...\n";
	if (listen(_socket, 1024) == -1)
		return;
	action.fd = _socket;
	action.events = POLLIN;
	action.revents = 0;
	std::cout << "server: running...\n";
	while (_run){
		std::cout << "server: waiting client...\n";
		while (poll(&action, 1, 0) == 0 && _run);
		if (_run)
			handle_client();
	}
	if (_clients.size() > 0){
		std::cout << "server: some client still running...\n";
		while (_clients.size() > 0);
	}
	std::cout << "server: all thing terminated\n";
}

void	server::stop()
{
	std::cout << "server: trying to stop...\n";
	_run = false;
	if (_socket != -1)
		close(_socket);
	_socket = -1;
	std::cout << "server: stopped\n";
}

std::map<int, client *>	&server::get_clients()
{
	return (_clients);
}

unsigned short	server::get_port() const noexcept
{
	return (_port);
}

void	server::set_clients(std::map<int, client *> &value)
{
	_clients = value;
}

std::list<command>	&server::get_responses()
{
	return (_responses);
}

void	server::add_to_log(command &com)
{
	std::ofstream	file("logs.txt", std::ofstream::out | std::ofstream::app);

	if (!file.is_open())
		return;
	file << "response (" << com.get_file() << ") - " << command::convert_info(com.get_info()) << ": " << com.get_response() << std::endl;
	file.close();
}