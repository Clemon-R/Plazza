/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** parser
*/

#include "utils/commands/parser.hpp"
#include <algorithm>

std::map<std::string, Information>	commandParser::_list = {
	{"PHONE_NUMBER", Information::PHONE_NUMBER},
	{"IP_ADDRESS", Information::IP_ADDRESS},
	{"EMAIL_ADDRESS", Information::EMAIL_ADDRESS}
};

static void	clean_str(std::string &line)
{
	std::replace(line.begin(),line.end(), '\n', ' ');
	std::replace(line.begin(),line.end(), '\r', ' ');
	std::replace(line.begin(),line.end(), '\t', ' ');
}

Information	commandParser::get_action(const std::string &action)
{
	Information	result = Information::UNKNOW;

	std::cout << "parser: action - " << action;
	if (_list.find(action) != _list.end())
		result = _list[action];
	std::cout << " : " << result << std::endl;
	return (result);
}

static void	add_command(std::list<command> &list, Information action, const std::string &name)
{
	command	com(name, action);

	std::cout << "parser: action - " << action << " on file - " << name << std::endl;
	list.push_back(com);
}

std::list<command>	commandParser::parse_line(std::string &line)
{
	int		count = 0;
	std::list<command>	result;
	Information	action = Information::NONE;
	int	i;

	std::cout << "parser: new line - " << line << std::endl;
	for (i = line.size() - 1;i >= 0 && action != Information::UNKNOW;i -= 1){
		if (line.at(i) != ' ')
			count++;
		else if (count > 0){
			if (action == Information::NONE)
				action = get_action(line.substr(i + 1, count));
			else
				add_command(result, action, line.substr(i + 1, count));
			count = 0;
		}
	}
	if (count > 0)
		add_command(result, action, line.substr(i + 1, count));
	return (result);
}

static bool	compare_commands(const command &first, const command &second)
{
	return (true);
}

std::list<command>	commandParser::parse_file(FILE *fd)
{
	int	len = 0;
	char	*line = 0;
	std::size_t	size = 0;
	std::string	str;
	std::string	tmp;

	std::list<command>	result;
	int	pos;

	std::cout << "parser: parse file - " << fd << std::endl;
	while ((len = getline(&line, &size, fd)) != -1){
		str = std::string(line);
		clean_str(str);
		while ((pos = str.find(";")) != std::string::npos){
			tmp = str.substr(0, pos);
			result.merge(parse_line(tmp), compare_commands);
			str = str.substr(pos + 1);
		}
		result.merge(parse_line(str), compare_commands);
	}
	std::cout << "parser: number of commands - " << result.size() << std::endl;
	return (result);
}