/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** command
*/

#ifndef COMMAND_HPP_
	#define COMMAND_HPP_

	#include <iostream>

enum	Information
{
	PHONE_NUMBER,
	EMAIL_ADDRESS,
	IP_ADDRESS
};

class command
{
public:
	command(const std::string &, const Information);
	~command();

	const std::string	&get_file() const noexcept;
	const Information	get_info() const noexcept;
private:
	std::string	_file;
	Information	_info;
};
#endif /* !COMMAND_HPP_ */
