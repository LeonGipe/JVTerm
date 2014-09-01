#ifndef WINSHOWMESSAGE_HPP
#define WINSHOWMESSAGE_HPP

#include <ncurses.h>
#include <string>
#include <vector>

class winShowMessageClass
{
public:
	winShowMessageClass();
	winShowMessageClass(int ncolumn, int nline);
	~winShowMessageClass();
	void createWin(int ncolumn, int nline);
	void refresh();
	void addMessage(std::string message);
	void scrollWin(int value);
private:
	WINDOW* win;
	bool firstMessage;
};

#endif
