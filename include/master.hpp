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
	#include "graphic/sfml.hpp"

class master
{
public:
	master();
	~master();

	bool	init_graphic();
private:
	std::unique_ptr<sfml>	_graphic;
};
#endif /* !MASTER_HPP_ */
