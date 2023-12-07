#pragma once
#include <vector>
#include <iostream>

class Chat
{
private:
	std::vector<std::pair<std::string, std::string>> m_messages;
public:
	std::vector<std::pair<std::string, std::string>> getChat();
	void WriteMessage(std::pair<std::string, std::string> message);
};

