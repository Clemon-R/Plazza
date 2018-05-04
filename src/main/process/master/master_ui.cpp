/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master_ui
*/

#include "main/process/master/master.hpp"
#include "main/process/master/master_ui.hpp"
#include <dirent.h>

/* Utility functions */

void	master_ui::my_set_position(sf::Text *text, int gap)
{
	sf::FloatRect	rect;

	rect = text->getLocalBounds();
	text->setOrigin(rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);
	text->setPosition(sf::Vector2f(_window.getSize().x / 2.0f,
		_window.getSize().y / 2.0f + gap));
}

std::string	string_converter(char *old_string)
{
	std::string	new_string(old_string);

	return (new_string);
}

static bool	compare_commands_ui(const command &first, const command &second)
{
	return (true);
}

/* Constructor */

master_ui::master_ui(const int max) : master(max)
{
	_actual_page = 0;
}

/* Init functions */

bool	master_ui::init_graphic()
{
	if (!_graphic_mode)
		return (false);
	std::cout << "master: graphic needed\nmaster: running init...\n";
	_graphic.reset(nullptr);
	return (true);
}

void	master_ui::init_first_page()
{
	sf::FloatRect	rect;

	if (!_font.loadFromFile("fonts/font1.ttf"))
		exit(84);
	first_page_choices[0].setFont(_font);
	first_page_choices[0].setString("Select file to scrap");
	first_page_choices[0].setCharacterSize(20);
	my_set_position(&first_page_choices[0], -40);
	first_page_choices[1].setFont(_font);
	first_page_choices[1].setString("Enter commands manuallly");
	first_page_choices[1].setCharacterSize(20);
	my_set_position(&first_page_choices[1], 0);
	first_page_choices[2].setFont(_font);
	first_page_choices[2].setString("Quit");
	first_page_choices[2].setCharacterSize(20);
	my_set_position(&first_page_choices[2], 40);
}

void	master_ui::init_second_page()
{
	DIR	*dir = opendir("files");
	struct dirent	*dir_struct;

	if (dir == NULL){
		_window.close();
		std::cerr << "Failed to open directory." << std::endl;
	}
	while (dir_struct = readdir(dir)){
		if (dir_struct->d_name[0] != '.' && dir_struct->d_type == DT_REG)
			_file_list.push_back(string_converter(dir_struct->d_name));
	}
	closedir(dir);
}


/* First page */

void	master_ui::draw_first_page(int whichOne)
{
	if (whichOne == 0){
		first_page_choices[0].setStyle(sf::Text::Underlined);
		first_page_choices[1].setStyle(sf::Text::Regular);
		first_page_choices[2].setStyle(sf::Text::Regular);
	}else if (whichOne == 1){
		first_page_choices[0].setStyle(sf::Text::Regular);
		first_page_choices[1].setStyle(sf::Text::Underlined);
		first_page_choices[2].setStyle(sf::Text::Regular);
	}else if (whichOne == 2){
		first_page_choices[0].setStyle(sf::Text::Regular);
		first_page_choices[1].setStyle(sf::Text::Regular);
		first_page_choices[2].setStyle(sf::Text::Underlined);
	}
	_window.draw(first_page_choices[0]);
	_window.draw(first_page_choices[1]);
	_window.draw(first_page_choices[2]);
}

void	master_ui::first_page()
{
	sf::Event	event;
	static int	whichOne = 0;

	while (_window.pollEvent(event)){
		if (event.type == sf::Event::Closed ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_window.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			whichOne += (whichOne > 1) ? -2 : 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			whichOne -= (whichOne < 1) ? -2 : 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
			if (whichOne == 0)
				_actual_page = 1;
			else if (whichOne == 1)
				_actual_page = 2;
			else
				_window.close();
		}
	}
	draw_first_page(whichOne);
}

/* Second page */

void	master_ui::draw_second_page(int whichOne)
{
	sf::Text	text;
	int	pos = -20 * _file_list.size();
	int	actual_printed = 0;

	for(auto inside : _file_list){
		text.setFont(_font);
		text.setString(inside);
		text.setCharacterSize(20);
		if (actual_printed == whichOne)
			text.setStyle(sf::Text::Underlined);
		else
			text.setStyle(sf::Text::Regular);
		my_set_position(&text, pos);
		_window.draw(text);
		pos += 40;
		actual_printed += 1;
	}
}

void	master_ui::second_page()
{
	sf::Event	event;
	int	nb_element = _file_list.size();
	static int	whichOne = 0;

	while (_window.pollEvent(event)){
		if (event.type == sf::Event::Closed ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_actual_page = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			whichOne += (whichOne > nb_element - 2) ? -nb_element + 1 : 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			whichOne -= (whichOne < 1) ? -nb_element + 1: 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			_commands.merge(commandParser::parse_line(
				_file_list.at(whichOne)), compare_commands_ui);
	}
	draw_second_page(whichOne);
}

/* Third page */

void	master_ui::draw_third_page()
{

}

void	master_ui::third_page()
{
	std::size_t	size = 0;
	sf::Event	event;
	static sf::String	entry;
	static sf::Text	to_display;

	while (_window.pollEvent(event)){
		if (event.type == sf::Event::Closed ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_actual_page = 0;
		if (event.type == sf::Event::TextEntered){
			if (event.text.unicode > 31 && event.text.unicode < 128){
				entry += event.text.unicode;
				std::cout << entry.toAnsiString() << std::endl;
			}
			else if (event.text.unicode == 13){
				std::cout << entry.toAnsiString() << std::endl;
				to_display.setFont(_font);
				to_display.setCharacterSize(20);
				to_display.setString(entry);
				my_set_position(&to_display, 0);
				entry.clear();
			}
		}
	}
	_window.draw(to_display);
}

/* Menu */

void	master_ui::run_menu()
{
	if (_actual_page == 0)
		first_page();
	else if (_actual_page == 1)
		second_page();
	else if (_actual_page == 2)
		third_page();
}

void	master_ui::run_interface(std::mutex &lock)
{
	sf::Vector2i	pos;

	pos.x = sf::VideoMode::getDesktopMode().width / 2 - 540;
	pos.y = sf::VideoMode::getDesktopMode().height / 2 - 420;
	_window.create(sf::VideoMode(1080, 840), "The Plazza");
	_window.setPosition(pos);
	init_first_page();
	init_second_page();
	while (_window.isOpen()){
		_window.clear(sf::Color::Black);
		run_menu();
		_window.display();
	}
	_run = false;
}