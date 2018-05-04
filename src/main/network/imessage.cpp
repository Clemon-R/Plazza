/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** imessage
*/

#include "main/network/imessage.hpp"

imessage::imessage(char id) : _id(id)
{
	_id = id;
}

void	imessage::write_int(int value)
{
	char	result[4];

	for (int i = 3;i >= 0;i--){
		result[i] = static_cast<char>(value & 0xff);
		value = value >> 8;
	}
	for (int i = 0;i < 4;i++)
		_encode += result[i];
}

void	imessage::write_char(char c)
{
	_encode += c;
}

void	imessage::write_string(const std::string &value)
{
	write_int(value.size());
	for (int i = 0;i < value.size();i++)
		_encode += value.at(i);
}

int	imessage::get_int()
{
	int	value = 0;

	for (int i = 0;i < 4;i++){
		value = value << 8;
		value += _decode[i];
	}
	_decode += 4;
	return (value);
}

char	imessage::get_char()
{
	char	c = _decode[0];

	_decode += 1;
	return (c);
}

std::string	imessage::get_string()
{
	int	len = get_int();
	std::string	result;
	
	for (int i = 0;i < len;i++){
		result += _decode[i];
	}
	_decode += len;
	return (result);
}

const std::string	&imessage::get_buff()
{
	return (_encode);
}