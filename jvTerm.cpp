#include <functional>

#include "jvTerm.hpp"

jvTermClass::jvTermClass(std::string topic, std::string pseudo, std::string mdpasse)
{
	int baseWidthBaseWindow;
	int baseHeightBaseWindow;

	postMessageHasEnd = false;
	getMessageHasEnd = false;

	jvcPostManager.init(topic, pseudo, mdpasse);

	getmaxyx(stdscr, baseHeightBaseWindow, baseWidthBaseWindow);

	winShowMessage.createWin(baseWidthBaseWindow, baseHeightBaseWindow - 2);
	winPostMessage.createWin(baseWidthBaseWindow, baseHeightBaseWindow - 2);

	raw();
	nl();
	noecho();
	timeout(1000);
	keypad(stdscr, true);

	refresh();
	winPostMessage.refresh();
}

jvTermClass::~jvTermClass()
{
	if(postMessageThread.get() != nullptr)
	{
		if(postMessageThread->joinable() == true)
		{
			postMessageThread->join();
		}
	}
	if(getMessageThread.get() != nullptr)
	{
		if(getMessageThread->joinable() == true)
		{
			getMessageThread->join();
		}
	}
}

void jvTermClass::run()
{
	std::chrono::steady_clock::time_point now;
	std::chrono::duration<double> interval;
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
				if(postMessageThread.get() == nullptr)
				{
					postMessageThread.reset(new std::thread(std::bind(&jvTermClass::postMessage, this)));
				}

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

		if(postMessageHasEnd == true)
		{
			postMessageThread->join();
			postMessageThread.reset();
			postMessageHasEnd = false;
		}
		if(getMessageHasEnd == true)
		{
			getMessageThread->join();
			getMessageThread.reset();
			getMessageHasEnd = false;
		}

		now = std::chrono::steady_clock::now();
		interval = std::chrono::duration_cast<std::chrono::duration<double>>(now  - lastCheck);

		if(interval.count() > 4)
		{
			updateMessages();
		}

		winPostMessage.refresh();
	}
}

void jvTermClass::updateMessages()
{
	if(getMessageThread.get() == nullptr)
	{
		getMessageThread.reset(new std::thread(std::bind(&jvTermClass::getLastMessages, this)));
	}
}

void jvTermClass::postMessage()
{
	std::unique_lock<std::mutex> lock(mutex);
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	std::chrono::duration<double> interval = std::chrono::duration_cast<std::chrono::duration<double>>(now  - lastCheck);

	while(interval.count() < 1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		now = std::chrono::steady_clock::now();
		interval = std::chrono::duration_cast<std::chrono::duration<double>>(now - lastCheck);
	}

	jvcPostManager.postMessage(winPostMessage.getMessagePostAndErase());
	winPostMessage.refresh();

	postMessageHasEnd = true;
}

void jvTermClass::getLastMessages()
{
	std::unique_lock<std::mutex> lock(mutex);
	std::list<std::string> messages = jvcPostManager.getLastMessages();

	for(std::string message : messages)
	{
		winShowMessage.addMessage(message);
	}

	lastCheck = std::chrono::steady_clock::now();
	winPostMessage.refresh();

	getMessageHasEnd = true;
}
