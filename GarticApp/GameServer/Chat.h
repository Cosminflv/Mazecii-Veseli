#pragma once
#include <vector>
#include <iostream>

class Chat
{
public:
	std::vector<std::pair<std::string, std::string>> getChatVector();
	void WriteMessage(std::pair<std::string, std::string> message);
private:	
	std::vector<std::pair<std::string, std::string>> m_messages;
};

