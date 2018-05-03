/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** slave
*/

#include "main/process/slave/slave.hpp"
#include "utils/utils.hpp"
#include <unistd.h>
#include <arpa/inet.h>

slave::slave(unsigned short port) : _parent(getpid()), _port(port), _socket(-1), _protocol(getprotobyname("TCP"))
{
	int	process = -1;

	std::cout << "slave (parent): parent process - " << getpid() << std::endl;
	process = fork();
	if (process == 0){
		std::cout << "slave: process - " << getpid() << std::endl;
		this->run();
	}
	else if (process > 0)
		std::cout << "slave (parent): new process has been created\n";
}

slave::~slave()
{
	if (_parent == getpid()){
		std::cout << "slave (parent): dead\n";
		return;
	}
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
	std::cout << "slave: successfull connected\n";
}

void	slave::run()
{
	std::size_t	last = utils::get_seconds();

	std::cout << "slave: running... " << last << "\n";
	connect_to_server();
	while (utils::get_seconds() - last < 5){
	}
	end_run();	
}

void	slave::end_run()
{
	std::cout << "slave: dead\n";
}