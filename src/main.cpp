/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main
*/

#include "main.hpp"
#include "main/master.hpp"
#include <cctype>
#include <memory>

static bool	check_error(int argc, char **argv)
{
	if (argc != 2){
		std::cerr << "main: need just one parameter.\n";
		return (true);
	}
	else if (!isdigit(argv[1][0])){
		std::cerr << "main: need a number.\n";
		return (true);
	}
	return (false);
}

int	main(int argc, char **argv)
{
	if (check_error(argc, argv))
		return (84);
	init_plazza(std::atoi(argv[1]));
	return (0);
}