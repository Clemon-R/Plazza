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

void	server::pack_all_socket(struct pollfd **actions)
{
	int	i = 1;

	(*actions)[0].fd = _socket;
	(*actions)[0].events = POLLIN;
	(*actions)[0].revents = 0;
	for (const auto &current : _clients){
		(*actions)[i].fd = current.second->get_socket();
		(*actions)[i].events = POLLIN;
		(*actions)[i].revents = 0;
		i++;
	}
}

void	server::handle_client()
{
	int	client_fd = 0;
	struct sockaddr_in	s_client_in;
	socklen_t		s_client_size = sizeof(s_client_in);
	std::unique_ptr<client>	current;

	std::cout << "server: action on server\n";
	client_fd = accept(_socket, (struct sockaddr *)&s_client_in, &s_client_size);
	if (client_fd == -1)
		return;
	current.reset(new client(*this, client_fd));
	_clients.insert(std::pair<int, std::unique_ptr<client>>(client_fd, std::move(current)));
}

bool	server::handle_action(struct pollfd *actions, std::size_t size)
{
	std::map<int, std::unique_ptr<client>>::iterator	it;

	for (int i = 0;i < size;i++){
		if (!(actions[i].revents & POLLIN))
			continue;
		std::cout << "server: action on - " << actions[i].fd << std::endl;
		if (actions[i].fd == _socket)
			handle_client();
		else if ((it = _clients.find(actions[i].fd)) != _clients.end())
			(*it).second->reception_packet();
	}
	return (true);
}

void	server::run()
{
	struct pollfd	*actions = nullptr;
	int	fd;

	std::cout << "server: starting...\n";
	if (listen(_socket, 1024) == -1)
		return;
	std::cout << "server: running...\n";
	while (_run){
		actions = new struct pollfd[_clients.size() + 1];
		if (!actions)
			break;
		std::cout << "server: preparing poll event...\n";
		pack_all_socket((struct pollfd **)&actions);
		std::cout << "server: waiting action...\n";
		while (poll(actions, _clients.size() + 1, 1) == 0 && _run);
		handle_action(actions, _clients.size() + 1);
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