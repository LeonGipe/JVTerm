#include "winShowMessage.hpp"

winShowMessageClass::winShowMessageClass()
{
	firstMessage = true;
}

winShowMessageClass::winShowMessageClass(int ncolumn, int nline)
{
	createWin(ncolumn, nline);
}

winShowMessageClass::~winShowMessageClass()
{
	delwin(win);
}

void winShowMessageClass::createWin(int ncolumn, int nline)
{
	win = newwin(nline, ncolumn, 0, 0);
	scrollok(win, true);
}

void winShowMessageClass::refresh()
{
	wrefresh(win);
}

void winShowMessageClass::addMessage(std::string message)
{
	if(firstMessage == false)
	{
		waddch(win, '\n');
	}
	firstMessage = false;

	waddstr(win, message.c_str());

	refresh();
}

void winShowMessageClass::scrollWin(int value)
{
	wscrl(win, value);
	refresh();
}
