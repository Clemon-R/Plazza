/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** command
*/

#include "utils/commands/command.hpp"
#include "main/network/message_handler.hpp"
#include <regex>
#include <fstream>

command::command() : command("", Information::NONE)
{
}

command::command(const std::string &file, const Information info) : _file(file), _info(info)
{
}

command::~command()
{
}

command	&command::operator=(const command &copy)
{
	this->_file = copy._file;
	this->_info = copy._info;
	return (*this);
}

void	command::set_file(std::string &file)
{
	this->_file = file;
}

void	command::set_info(Information info)
{
	this->_info = info;
}

const std::string	&command::get_file() const noexcept
{
	return (this->_file);
}

const Information	command::get_info() const noexcept
{
	return (this->_info);
}

void	command::run(client &client, std::thread **src)
{
	std::cout << "command: treating command...\n";
	switch (_info){
		case Information::PHONE_NUMBER:
		phone_number(client);
		break;
		case Information::IP_ADDRESS:
		ip_address(client);
		break;
		case Information::EMAIL_ADDRESS:
		email_address(client);
		break;
	}
	*src = nullptr;
}

std::string	command::read_file()
{
	std::ifstream	file(_file);
	std::string	content;
	std::string	line;

	if (!file.is_open())
		return (content);
	while (std::getline(file, line)){
		content.append(line);
		content += 10;
	}
	file.close();
	return (content);
}

void	command::phone_number(client &client)
{
	std::regex	r("[0-99]{2}\\s{0,1}[0-99]{2}\\s{0,1}[0-99]{2}\\s{0,1}[0-99]{2}\\s{0,1}[0-99]{2}");
	std::smatch	matchs;
	std::string	content(read_file());

	while (std::regex_search(content, matchs, r)){
		for (const std::string &match : matchs){
			std::cout << "command: match - " << match << std::endl;
			_response = match;
			message_handler::send_packet(client, 1, this);
			if (client.get_slave())
				message_handler::send_packet(client, 2, nullptr);
		}
		content = matchs.suffix().str();
	}
}

void	command::ip_address(client &client)
{
	std::regex	r("[0-9]{1,3}+[.][0-9]{1,3}+[.][0-9]{1,3}+[.][0-9]{1,3}+");
	std::smatch	matchs;
	std::string	content(read_file());

	while (std::regex_search(content, matchs, r)){
		for (const std::string &match : matchs){
			std::cout << "command: match - " << match << std::endl;
			_response = match;
			message_handler::send_packet(client, 1, this);
			if (client.get_slave())
				message_handler::send_packet(client, 2, nullptr);
		}
		content = matchs.suffix().str();
	}
}

void	command::email_address(client &client)
{
	std::regex	r("[a-zA-Z0-9._-]{1,}+@[a-zA-Z0-9-]{1,}+[.[a-zA-Z0-9-]+]*");
	std::smatch	matchs;
	std::string	content(read_file());

	while (std::regex_search(content, matchs, r)){
		for (const std::string &match : matchs){
			std::cout << "command: match - " << match << std::endl;
			_response = match;
			message_handler::send_packet(client, 1, this);
			if (client.get_slave())
				message_handler::send_packet(client, 2, nullptr);
		}
		content = matchs.suffix().str();
	}
}

void	command::set_response(std::string &value)
{
	_response = value;
}

const std::string &command::get_response() const noexcept
{
	return (_response);
}

std::string	command::convert_info(Information info)
{
	std::string	result = "UNKNOW";

	switch (info){
		case Information::PHONE_NUMBER:
		result = "PHONE_NUMBER";
		break;
		case Information::IP_ADDRESS:
		result = "IP_ADDRESS";
		break;
		case Information::EMAIL_ADDRESS:
		result = "EMAIL_ADDRESS";
		break;
	}
	return (result);
}