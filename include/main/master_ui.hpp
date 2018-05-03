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
	#include <experimental/filesystem>

class master_ui : public master
{
public:
	master_ui(const int);
	void	run_interface() override final;
	void	run_main_menu();
	void	run_display_file();
	bool	init_graphic();
	void	init_first_page();
	void	init_second_page();
	void	my_set_position(sf::Text *, int);
	void	draw_first_page(int);
	void	first_page();
	void	draw_second_page();
	void	second_page();
	void	draw_third_page();
	void	third_page();
private:
	std::unique_ptr<sfml>	_graphic;
	std::string	_file;
	sf::RenderWindow	_window;
	sf::Font	_font;
	sf::Text	first_page_choices[2];
	sf::String	*_file_list;
	int	_actual_page;
};
#endif /* !MASTER_UI_HPP_ */
