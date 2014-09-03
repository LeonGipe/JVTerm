#ifndef JVCPOSTMANAGER_HPP
#define JVCPOSTMANAGER_HPP

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
#include <boost/regex.hpp>

class jvcPostManagerClass
{
public:
	jvcPostManagerClass();
	void init(std::string newTopic, std::string newPseudo, std::string newMdpasse);
	std::list<std::string> getLastMessages();
	void postMessage(std::string message);
private:
	curlpp::Cleanup myCleanup;
	boost::regex messagesRegex;
	boost::regex messageIdRegex;
	boost::regex messagePseudoRegex;
	boost::regex grepFormRegex;
	boost::regex grepInputRegex;
	boost::regex matchSmileyRegex;
	boost::regex matchLinkRegex;
	std::string lastSources;
	int idOfLastMessage;
	std::string pseudo;
	std::string mdpasse;
	std::string topic;
};

#endif
