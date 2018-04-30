/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** command
*/

#include "utils/commands/command.hpp"

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
