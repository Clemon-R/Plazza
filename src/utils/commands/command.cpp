/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** command
*/

#include "utils/commands/command.hpp"

command::command(const std::string &file, const Information info) : _file(file), _info(info)
{
	std::cout << "command: new command created.\n";
	std::cout << "command: on file - " << file << "." << std::endl;
	std::cout << "command: action - " << info << "." << std::endl;
}

command::~command()
{
	std::cout << "command: destroyed.\n";
}

const std::string	&command::get_file() const noexcept
{
	return (this->_file);
}

const Information	command::get_info() const noexcept
{
	return (this->_info);
}
