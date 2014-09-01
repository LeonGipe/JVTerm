#include "jvTerm.hpp"

jvTermClass::jvTermClass(std::string topic, std::string pseudo, std::string mdpasse)
{
	int baseWidthBaseWindow;
	int baseHeightBaseWindow;

	jvcPostManager.init(topic, pseudo, mdpasse);

	getmaxyx(stdscr, baseHeightBaseWindow, baseWidthBaseWindow);

	winShowMessage.createWin(baseWidthBaseWindow, baseHeightBaseWindow - 2);
	winPostMessage.createWin(baseWidthBaseWindow, baseHeightBaseWindow - 2);

	raw();
	nl();
	noecho();
	keypad(stdscr, true);

	refresh();
	winPostMessage.refresh();
}

void jvTermClass::run()
{
	int c = 0;

	while((c = getch()) != KEY_F(10))
	{
		if(c != ERR)
		{
			if(c == KEY_UP)
			{
				winShowMessage.scrollWin(-1);
			}
			else if(c == KEY_DOWN)
			{
				winShowMessage.scrollWin(1);
			}
			else if(c == '\n')
			{
				jvcPostManager.postMessage(winPostMessage.getMessagePostAndErase());

				updateMessages();
			}
			else if(c == KEY_BACKSPACE)
			{
				winPostMessage.eraseLastChar();
			}
			else if(c == KEY_F(5))
			{
				updateMessages();
			}
			else if(c > 31 && c < 255 && c != 127)
			{
				winPostMessage.addChar(c);
			}
		}

		winPostMessage.refresh();
	}
}

void jvTermClass::updateMessages()
{
	std::list<std::string> messages = jvcPostManager.getLastMessages();

	for(std::string message : messages)
	{
		winShowMessage.addMessage(message);
	}
}
