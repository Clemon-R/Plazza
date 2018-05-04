/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** imessage
*/

#ifndef IMESSAGE_HPP_
	#define IMESSAGE_HPP_

	#include <memory>
	#include "utils/commands/command.hpp"

class imessage
{
public:
	imessage(char id);
	virtual ~imessage() = default;

	void	write_int(int);
	void	write_char(char);
	void	write_string(const std::string &);

	int	get_int();
	char	get_char();
	std::string	get_string();

	virtual std::unique_ptr<command>	decode(const char *) = 0;
	virtual void	encode(command &com) = 0;

	const std::string	&get_buff();
protected:
	std::string	_encode;
	const char	*_decode;
	char	_id;
};
#endif /* !IMESSAGE_HPP_ */
