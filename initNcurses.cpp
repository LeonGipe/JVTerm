#include <locale.h>

#include "initNcurses.hpp"

initNcursesClass::initNcursesClass()
{
	setlocale(LC_ALL, "");
	initscr();
}

initNcursesClass::~initNcursesClass()
{
	endwin();
}
