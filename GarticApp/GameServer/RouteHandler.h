#pragma once
#include "Game.h"
#include "Game.h"

class RouteHandler
{
public:
	RouteHandler();
	RouteHandler(const Game& game);


	bool CheckEnteredMessage(const std::string& message);
	void AddPlayer(PlayerPtr newPlayer);
	void WriteMessage(const std::string& username, const std::string& message);

private:
	Game m_game;

};

