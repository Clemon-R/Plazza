/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main
*/

#include "main.hpp"
#include "master.hpp"
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
	std::unique_ptr<master>	mt;

	if (check_error(argc, argv))
		return (84);
	mt.reset(new master(std::atoi(argv[1])));
	init_plazza(*mt);
	return (0);
}