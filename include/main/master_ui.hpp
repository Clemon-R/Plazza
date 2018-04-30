/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master_ui
*/

#ifndef MASTER_UI_HPP_
	#define MASTER_UI_HPP_

	#include "main/master.hpp"
	#include "graphic/sfml.hpp"

class master_ui : public master
{
public:
	master_ui(const int);
	void	run_interface() override final;
	bool	init_graphic();
private:
	std::unique_ptr<sfml>	_graphic;
};
#endif /* !MASTER_UI_HPP_ */
