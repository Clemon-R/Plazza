/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master
*/

#ifndef MASTER_HPP_
	#define MASTER_HPP_

	#include <memory>
	#include <iostream>
	#include <list>
	#include <thread>
	#include <mutex>
	#include <map>
	#include "utils/commands/command.hpp"
	#include "main/slave.hpp"

class master
{
public:
	master(const int);
	~master();

	virtual void	run_interface() = 0;
	void	run_dispatch();
	void	run();
	void	set_commands(const std::list<command> &);
	void	set_graphic_mode() noexcept;
private:
	std::pair<std::unique_ptr<std::thread>, std::unique_ptr<slave>>	create_slave();
protected:
	std::map<std::unique_ptr<std::thread>, std::unique_ptr<slave>>	_slaves;
	const std::size_t	_max_thread;
	std::list<command>	_commands;
	bool			_graphic_mode;
	bool			_run;
};
#endif /* !MASTER_HPP_ */
