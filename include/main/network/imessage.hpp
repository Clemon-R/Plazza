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
	#include "main/network/client/client.hpp"

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

	virtual std::unique_ptr<command>	decode(client &client, const char *) = 0;
	virtual void	encode(client &client, command *com) = 0;

	const std::string	&get_buff();
	int	get_len();
	void	set_len(int);
protected:
	std::string	_encode;
	const char	*_decode;
	int	_len;
	char	_id;
};
#endif /* !IMESSAGE_HPP_ */
