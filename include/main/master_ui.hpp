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
	void	run_menu();
	bool	init_graphic();
	void	init_choices();
	void	draw_choice(bool);
private:
	std::unique_ptr<sfml>	_graphic;
	std::string	_file;
	sf::RenderWindow	_window;
	sf::Font	_font;
	sf::Text	choice[2];
};
#endif /* !MASTER_UI_HPP_ */
