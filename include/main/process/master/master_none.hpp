/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master_none
*/

#ifndef MASTER_NONE_HPP_
	#define MASTER_NONE_HPP_

	#include "main/process/master/master.hpp"

class master_none : public master
{
public:
	master_none(const int);
	void	run_interface() override final;
};
#endif /* !MASTER_NONE_HPP_ */
