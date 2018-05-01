/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** utils
*/

#include "utils/utils.hpp"

std::size_t	utils::get_seconds()
{
	time_t		timer;
	struct tm	y2k = {0};

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
	time(&timer);
	return (difftime(timer,mktime(&y2k)));
}