/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master_ui
*/

#include "main/master.hpp"
#include "main/master_ui.hpp"

master_ui::master_ui(const int max) : master(max)
{
	_actual_page = 0;
}

bool	master_ui::init_graphic()
{
	if (!_graphic_mode)
		return (false);
	std::cout << "master: graphic needed\nmaster: running init...\n";
	_graphic.reset(nullptr);
	return (true);
}

void	master_ui::my_set_position(sf::Text *text, int gap)
{
	sf::FloatRect	rect;

	rect = text->getLocalBounds();
	text->setOrigin(rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);
	text->setPosition(sf::Vector2f(_window.getSize().x / 2.0f,
		_window.getSize().y / 2.0f + gap));
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
	first_page_choices[1].setString("Enter commands manually");
	first_page_choices[1].setCharacterSize(20);
	my_set_position(&first_page_choices[1], 0);
	first_page_choices[2].setFont(_font);
	first_page_choices[2].setString("Quit");
	first_page_choices[2].setCharacterSize(20);
	my_set_position(&first_page_choices[2], 40);
}

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

void	master_ui::draw_second_page()
{
	sf::Text	test;

	test.setFont(_font);
	test.setString("This is the second page");
	test.setCharacterSize(20);
	my_set_position(&test, 0);
	_window.draw(test);
}

void	master_ui::second_page()
{
	sf::Event	event;

	while (_window.pollEvent(event)){
		if (event.type == sf::Event::Closed ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_window.close();
	}
	draw_second_page();
}

void	master_ui::draw_third_page()
{
	sf::Text	test;

	test.setFont(_font);
	test.setString("This is the third page");
	test.setCharacterSize(20);
	my_set_position(&test, 0);
	_window.draw(test);
}

void	master_ui::third_page()
{
	sf::Event	event;

	while (_window.pollEvent(event)){
		if (event.type == sf::Event::Closed ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_window.close();
	}
	draw_third_page();
}

void	master_ui::run_menu()
{
	sf::Vector2i	pos;

	pos.x = sf::VideoMode::getDesktopMode().width / 2 - 540;
	pos.y = sf::VideoMode::getDesktopMode().height / 2 - 420;
	_window.create(sf::VideoMode(1080, 840), "The Plazza");
	_window.setPosition(pos);
	init_first_page();
	while (_window.isOpen()){
		_window.clear(sf::Color::Black);
		if (_actual_page == 0)
			first_page();
		else if (_actual_page == 1)
			second_page();
		else if (_actual_page == 2)
			third_page();
		_window.display();
	}
	_run = false;
}

void	master_ui::run_interface()
{
	run_menu();
}