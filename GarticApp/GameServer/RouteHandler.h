#pragma once
#include "Game.h"
#include <random>

class RouteHandler
{
public:
	RouteHandler();
	RouteHandler(std::shared_ptr<Game> m_game);

	//Getters
	std::shared_ptr<Game> GetGame();


	bool CheckEnteredMessage(const std::string& message);
	void AddPlayer(const std::string& username);
	void WriteMessage(const std::string& username, const std::string& message);
	std::string PickWord(uint16_t difficulty);
	std::string HideTheWord(std::string word);
	std::string UpdateWord(std::string& word, std::string &currentWord);
	void CalculateScoreForGuesser(const std::string& username, std::vector<PlayerPtr>players, Timer& T);
private:
	std::shared_ptr<Game> m_game;
};

