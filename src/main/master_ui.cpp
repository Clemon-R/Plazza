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
}

bool	master_ui::init_graphic()
{
	if (!_graphic_mode)
		return (false);
	std::cout << "master: graphic needed\nmaster: running init...\n";
	_graphic.reset(nullptr);
	return (true);
}

void	master_ui::draw_choice(bool whichOne)
{
	if (whichOne){
		choice[0].setStyle(sf::Text::Underlined);
		choice[1].setStyle(sf::Text::Regular);
	}
	else{
		choice[0].setStyle(sf::Text::Regular);
		choice[1].setStyle(sf::Text::Underlined);
	}
	_window.draw(choice[0]);
	_window.draw(choice[1]);
}

void	master_ui::init_choices()
{
	sf::FloatRect	rect;

	if (!_font.loadFromFile("fonts/font1.ttf"))
		exit(84);
	choice[0].setFont(_font);
	choice[0].setString("Select file to scrap");
	choice[0].setCharacterSize(20);
	rect = choice[0].getLocalBounds();
	choice[0].setOrigin(rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);
	choice[0].setPosition(sf::Vector2f(_window.getSize().x / 2.0f,
		_window.getSize().y / 2.0f - 40));
	choice[1].setFont(_font);
	choice[1].setString("Enter commands manually");
	choice[1].setCharacterSize(20);
	rect = choice[1].getLocalBounds();
	choice[1].setOrigin(rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);
	choice[1].setPosition(sf::Vector2f(_window.getSize().x / 2.0f,
		_window.getSize().y / 2.0f));
}

void	master_ui::run_menu()
{
	sf::Event event;
	sf::Vector2i	pos;
	bool	whichOne = true;

	pos.x = sf::VideoMode::getDesktopMode().width / 2 - 540;
	pos.y = sf::VideoMode::getDesktopMode().height / 2 - 420;
	_window.create(sf::VideoMode(1080, 840), "The Plazza");
	_window.setPosition(pos);
	init_choices();
	while (_window.isOpen()){
		while (_window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				_window.close();
			if (event.key.code == sf::Keyboard::Escape)
				_window.close();
			if (event.key.code == sf::Keyboard::Down)
				whichOne = false;
			if (event.key.code == sf::Keyboard::Up)
				whichOne = true;
		}
		_window.clear(sf::Color::Black);
		draw_choice(whichOne);
		_window.display();
	}
	_run = false;
}

void	master_ui::run_interface()
{
	run_menu();
}