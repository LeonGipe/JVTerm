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
	void init(std::string topic, std::string newPseudo, std::string newMdpasse);
	std::list<std::string> getLastMessages();
	void postMessage(std::string message);
private:
	curlpp::Cleanup myCleanup;
	curlpp::Easy requestGet;
	curlpp::Easy requestPost;
	std::ostringstream oss;
	std::ostringstream output;
	boost::regex messagesRegex;
	boost::regex messageIdRegex;
	boost::regex grepFormRegex;
	boost::regex grepInputRegex;
	std::string lastSources;
	int idOfLastMessage;
	std::string pseudo;
	std::string mdpasse;
};

#endif
