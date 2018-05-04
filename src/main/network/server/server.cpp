/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** server
*/

#include "main/network/server/server.hpp"

server::server() : _protocol(getprotobyname("TCP")), _socket(-1), _run(true), _port(0)
{
	char	option = 1;
	socklen_t addrlen = sizeof(_config);

	std::cout << "server: creating server...\n";
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
	std::cout << "server: destroying server...\n";
	_run = false;
	if (_socket != -1)
		close(_socket);
	std::cout << "server: destroyed\n";
}

void	server::handle_client()
{
	int	client_fd = 0;
	struct sockaddr_in	s_client_in;
	socklen_t		s_client_size = sizeof(s_client_in);
	std::unique_ptr<client>	current;
	std::unique_ptr<std::thread>	bg;
	client	*tmp;

	std::cout << "server: action on server\n";
	client_fd = accept(_socket, (struct sockaddr *)&s_client_in, &s_client_size);
	if (client_fd == -1)
		return;
	tmp = new client(this, client_fd);
	current.reset(tmp);
	_clients.insert(std::pair<int, std::unique_ptr<client>>(client_fd, std::move(current)));
	bg.reset(new std::thread([&tmp](){tmp->run();}));
	_clients_thread.insert(std::pair<int, std::unique_ptr<std::thread>>(client_fd, std::move(bg)));
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
		handle_client();
	}
	std::cout << "server: stopping\n";
}

void	server::stop()
{
	std::cout << "server: trying to stop...\n";
	_run = false;
}

std::map<int, std::unique_ptr<client>>	&server::get_clients()
{
	return (_clients);
}

unsigned short	server::get_port() const noexcept
{
	return (_port);
}