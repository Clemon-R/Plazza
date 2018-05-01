/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** slave
*/

#ifndef SLAVE_HPP_
	#define SLAVE_HPP_

	#include <thread>
	#include <memory>
	#include <iostream>

class slave
{
public:
	slave();
	~slave();

	void	run();
	void	end_run();
private:
	int	_parent;
};
#endif /* !SLAVE_HPP_ */
