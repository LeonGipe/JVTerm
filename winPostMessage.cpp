#include "winPostMessage.hpp"

winPostMessageClass::winPostMessageClass()
{
	//void
}

winPostMessageClass::winPostMessageClass(int ncolumn, int baseY)
{
	createWin(ncolumn, baseY);
}

winPostMessageClass::~winPostMessageClass()
{
	delwin(win);
}

void winPostMessageClass::createWin(int ncolumn, int baseY)
{
	column = ncolumn;

	win = newwin(2, ncolumn, baseY, 0);

	clearWin();
}

void winPostMessageClass::clearWin(bool andIndex)
{
	wclear(win);
	wmove(win, 0, 0);

	for(int i = 0; i < column; ++i)
	{
		waddch(win, '-');
	}

	wmove(win, 1, 0);

	if(andIndex == true)
	{
		index = 0;
	}
	else
	{
		waddstr(win, messagePost.substr(index, messagePost.size() - index).c_str());
	}
}

void winPostMessageClass::refresh()
{
	wrefresh(win);
}

void winPostMessageClass::addChar(int thisChar)
{
	int xPos;
	int yPos;

	waddch(win, thisChar);

	messagePost += thisChar;

	getyx(win, yPos, xPos);

	if(xPos >= column - 1)
	{
		++index;
		clearWin(false);
	}

	(void)yPos;
}

std::string winPostMessageClass::getMessagePostAndErase()
{
	std::string tmpMsg = messagePost;

	messagePost.clear();
	clearWin();

	return tmpMsg;
}

void winPostMessageClass::eraseLastChar()
{
	if(messagePost.size() > 0)
	{
		messagePost.erase(messagePost.size() - 1, 1);

		if(index > 0)
		{
			--index;
		}

		clearWin(false);
	}
}
