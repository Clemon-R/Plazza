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
	#include "utils/commands/command.hpp"

class master
{
public:
	master(const int);
	~master();

	virtual void	run_interface() = 0;
	void	run();
	void	set_commands(const std::list<command> &);
	void	set_graphic_mode() noexcept;
protected:
	const std::size_t	_max_thread;
	std::list<command>	_commands;
	bool			_graphic_mode;
	bool			_run;
};
#endif /* !MASTER_HPP_ */
