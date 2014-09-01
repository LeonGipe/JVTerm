#ifndef JVTERMCLASS_HPP
#define JVTERMCLASS_HPP

#include <thread>

#include "initNcurses.hpp"
#include "winPostMessage.hpp"
#include "winShowMessage.hpp"
#include "jvcPostManager.hpp"

class jvTermClass
{
public:
	jvTermClass(std::string topic, std::string pseudo, std::string mdpasse);
	void run();
	void updateMessages();
private:
	jvcPostManagerClass jvcPostManager;
	initNcursesClass initNcurses;
	winPostMessageClass winPostMessage;
	winShowMessageClass winShowMessage;
};

#endif
