#include <list>
#include <string>

#include "jvcPostManager.hpp"

jvcPostManagerClass::jvcPostManagerClass()
{
	idOfLastMessage = 0;

	messagesRegex.assign("<li class=\"post\">(.*?)</li>");
	messageIdRegex.assign("<div id=\"message_([^\"]+)\" class=\"");
	messagePseudoRegex.assign("<li class=\"pseudo\">\n<stron[^>]*>([^<]*)</strong>");
	grepFormRegex.assign("<form id=\"post\" name=\"post\" method=\"post\".*?</form>");
	grepInputRegex.assign("<input ([^=]*)=\"([^\"]*)\" ([^=]*)=\"([^\"]*)\" ([^=]*)=\"([^\"]*)\" />");
	matchSmileyRegex.assign("<img src=\"[^\"]+\" alt=\"([^\"]+)\" />");
	matchLinkRegex.assign("<a href=\"(mailto:)?([^\"]+)\".*?>.*?</a>");
}

void jvcPostManagerClass::init(std::string newTopic, std::string newPseudo, std::string newMdpasse)
{
	topic = newTopic;
	pseudo = newPseudo;
	mdpasse = newMdpasse;
}

std::list<std::string> jvcPostManagerClass::getLastMessages()
{
	std::list<std::string> newMessages;
	boost::smatch messages;
	boost::smatch messageId;
	boost::smatch messagePseudo;
	std::string sources;
	curlpp::Easy requestGet;
	std::ostringstream oss;
	std::list<std::string> headerGet;

	headerGet.push_back("User-Agent: JVTerm");
	headerGet.push_back("Content-Type: application/x-www-form-urlencoded");
	headerGet.push_back("Connection: Keep-Alive");
	headerGet.push_back("Cookie: lol=mdr");

	requestGet.setOpt(curlpp::options::HttpHeader(headerGet));
	requestGet.setOpt(curlpp::options::WriteStream(&oss));
	requestGet.setOpt(curlpp::options::Url(topic));

	requestGet.perform();

	sources = oss.str();
	lastSources = sources;
	oss.clear();

	while(boost::regex_search(sources, messages, messagesRegex))
	{
		std::string::size_type pos = std::string::npos;
		std::string thisNewMessage = messages.str(1);
		std::string pseudoOfThisMessage;
		int idOfThisMessage = 0;

		boost::regex_search(sources, messageId, messageIdRegex);
		idOfThisMessage = std::stoi(messageId.str(1));

		boost::regex_search(sources, messagePseudo, messagePseudoRegex);
		pseudoOfThisMessage = messagePseudo.str(1);

		if(idOfThisMessage > idOfLastMessage)
		{
			while((pos = thisNewMessage.find("\r")) != std::string::npos)
			{
				thisNewMessage.replace(pos, 1, "");
			}
			while((pos = thisNewMessage.find("\n")) != std::string::npos)
			{
				thisNewMessage.replace(pos, 1, "");
			}
			while((pos = thisNewMessage.find("<br />")) != std::string::npos)
			{
				thisNewMessage.replace(pos, 6, "\n");
			}
			while((pos = thisNewMessage.find("  ")) != std::string::npos)
			{
				thisNewMessage.replace(pos, 2, " ");
			}
			while((pos = thisNewMessage.find("&lt;")) != std::string::npos)
			{
				thisNewMessage.replace(pos, 4, "<");
			}
			while((pos = thisNewMessage.find("&gt;")) != std::string::npos)
			{
				thisNewMessage.replace(pos, 4, ">");
			}

			thisNewMessage = boost::regex_replace(thisNewMessage, matchSmileyRegex, "$1");
			thisNewMessage = boost::regex_replace(thisNewMessage, matchLinkRegex, "$2");

			newMessages.push_back(pseudoOfThisMessage + " | " + thisNewMessage);
			idOfLastMessage = idOfThisMessage;
		}

		sources = messages.suffix().str();
	}

	return newMessages;
}

void jvcPostManagerClass::postMessage(std::string message)
{
	std::string sources = lastSources;
	std::string dataPost;
	boost::smatch inputMatch;
	curlpp::Easy requestPost;
	std::ostringstream output;
	std::list<std::string> headerPost;

	headerPost.push_back("User-Agent: JVTerm");
	headerPost.push_back("Content-Type: application/x-www-form-urlencoded");
	headerPost.push_back("Connection: Keep-Alive");
	headerPost.push_back("Cookie: lol=mdr");

	requestPost.setOpt(curlpp::options::HttpHeader(headerPost));
	requestPost.setOpt(curlpp::options::WriteStream(&output));
	requestPost.setOpt(curlpp::options::Url("http://www.jeuxvideo.com/cgi-bin/jvforums/forums.cgi"));
	requestPost.setOpt(curlpp::options::CookieList(""));

	boost::regex_search(sources, inputMatch, grepFormRegex);
	sources = inputMatch.str(0);
	output.clear();

	while(boost::regex_search(sources, inputMatch, grepInputRegex))
	{
		if(inputMatch.str(1) == "type")
		{
			if(inputMatch.str(3) == "name")
			{
				dataPost.append(inputMatch.str(4) + "=" + inputMatch.str(6) + "&");
			}
			else
			{
				dataPost.append(inputMatch.str(6) + "=" + inputMatch.str(4) + "&");
			}
		}
		else if(inputMatch.str(3) == "type")
		{
			if(inputMatch.str(1) == "name")
			{
				dataPost.append(inputMatch.str(2) + "=" + inputMatch.str(6) + "&");
			}
			else
			{
				dataPost.append(inputMatch.str(6) + "=" + inputMatch.str(2) + "&");
			}
		}
		else
		{
			if(inputMatch.str(1) == "name")
			{
				dataPost.append(inputMatch.str(2) + "=" + inputMatch.str(4) + "&");
			}
			else
			{
				dataPost.append(inputMatch.str(4) + "=" + inputMatch.str(2) + "&");
			}
		}
		sources = inputMatch.suffix().str();
	}

	dataPost += "yournewmessage=" + message + "&newnom=" + pseudo + "&mdpasse=" + mdpasse + "&bool_log=0";

	requestPost.setOpt(curlpp::options::PostFields(dataPost));
	requestPost.setOpt(curlpp::options::PostFieldSize(dataPost.size()));

	requestPost.perform();
}
