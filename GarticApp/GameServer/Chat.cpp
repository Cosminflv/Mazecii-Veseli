#include "Chat.h"

std::vector<std::pair<std::string, std::string>> Chat::getChat()
{
	return m_messages;
}

void Chat::WriteMessage(std::pair<std::string, std::string> message)
{
	m_messages.push_back(message);
}
