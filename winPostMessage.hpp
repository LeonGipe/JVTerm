#ifndef WINPOSTMESSAGE_HPP
#define WINPOSTMESSAGE_HPP

#include <ncurses.h>
#include <string>

class winPostMessageClass
{
public:
	winPostMessageClass();
	winPostMessageClass(int ncolumn, int baseY);
	~winPostMessageClass();
	void createWin(int ncolumn, int baseY);
	void clearWin(bool andIndex = true);
	void refresh();
	void addChar(int thisChar);
	std::string getMessagePostAndErase();
	void eraseLastChar();
private:
	WINDOW* win;
	std::string messagePost;
	int column;
	int index;
};

#endif
