/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** slave
*/

#include "main/slave.hpp"
#include "utils/utils.hpp"
#include <unistd.h>

slave::slave() : _parent(getpid())
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

void	slave::run()
{
	std::size_t	last = utils::get_seconds();

	std::cout << "slave: running... " <<last << "\n";
	while (utils::get_seconds() - last < 5){
	}
	end_run();	
}

void	slave::end_run()
{
	std::cout << "slave: dead\n";
}