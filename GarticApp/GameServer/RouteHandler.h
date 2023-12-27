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
	int GetRandomIndex(int length);
	std::string UpdateWordWithLetters(std::string currentWord);
	std::string RevealLetter(std::string currentWord, int index, char letter);
private:
	Game m_game;

};

