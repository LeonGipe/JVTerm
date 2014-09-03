#ifndef JVTERMCLASS_HPP
#define JVTERMCLASS_HPP

#include <thread>
#include <mutex>
#include <memory>
#include <chrono>

#include "initNcurses.hpp"
#include "winPostMessage.hpp"
#include "winShowMessage.hpp"
#include "jvcPostManager.hpp"

class jvTermClass
{
public:
	jvTermClass(std::string topic, std::string pseudo, std::string mdpasse);
	~jvTermClass();
	void run();
	void updateMessages();
	void postMessage();
	void getLastMessages();
private:
	jvcPostManagerClass jvcPostManager;
	initNcursesClass initNcurses;
	winPostMessageClass winPostMessage;
	winShowMessageClass winShowMessage;
	std::mutex mutex;
	std::unique_ptr<std::thread> postMessageThread;
	std::unique_ptr<std::thread> getMessageThread;
	bool postMessageHasEnd;
	bool getMessageHasEnd;
	std::chrono::steady_clock::time_point lastCheck;
};

#endif
