/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** command
*/

#ifndef COMMAND_HPP_
	#define COMMAND_HPP_

	#include <iostream>
class client;
	#include "main/network/client/client.hpp"
	#include <thread>

enum	Information
{
	PHONE_NUMBER,
	EMAIL_ADDRESS,
	IP_ADDRESS,
	UNKNOW,
	NONE
};

class command
{
public:
	command();
	command(const std::string &, const Information);
	~command();

	void			set_file(std::string &);
	void			set_info(Information);
	void			set_response(std::string &);
	const std::string	&get_file() const noexcept;
	const Information	get_info() const noexcept;
	const std::string	&get_response() const noexcept;

	static std::string		convert_info(Information);

	void			run(client &client, std::thread **src);

	command	&operator=(const command &);
private:
	std::string	read_file();

	void	phone_number(client &client);
	void	ip_address(client &client);
	void	email_address(client &client);

	std::string	_file;
	Information	_info;
	std::string	_response;
};
#endif /* !COMMAND_HPP_ */
