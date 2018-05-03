/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master_ui
*/

#ifndef MASTER_UI_HPP_
	#define MASTER_UI_HPP_

	#include "main/process/master/master.hpp"
	#include "main/graphic/sfml.hpp"

class master_ui : public master
{
public:
	master_ui(const int);
	void	run_interface(void) override final;
	void	run_menu(void);
	void	run_display_file(void);
	bool	init_graphic(void);
	void	init_first_page(void);
	void	init_second_page(void);
	void	my_set_position(sf::Text *, int);
	void	draw_first_page(int);
	void	first_page(void);
	void	draw_second_page(void);
	void	second_page(void);
	void	draw_third_page(void);
	void	third_page(void);
	std::string	string_converter(char *);
private:
	std::unique_ptr<sfml>	_graphic;
	std::string	_file;
	sf::RenderWindow	_window;
	sf::Font	_font;
	sf::Text	first_page_choices[2];
	std::list<std::string>	_file_list;
	int	_actual_page;
};
#endif /* !MASTER_UI_HPP_ */
