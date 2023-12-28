#pragma once
#include "Game.h"
#include <random>

class RouteHandler
{
public:
	RouteHandler();
	RouteHandler(const Game& game);


	bool CheckEnteredMessage(const std::string& message);
	void AddPlayer(const std::string& username);
	void WriteMessage(const std::string& username, const std::string& message);
	std::string PickWord(uint16_t difficulty);
	std::string HideTheWord(std::string word);
	std::string UpdateWord(std::string& word);
private:
	Game m_game;

};

