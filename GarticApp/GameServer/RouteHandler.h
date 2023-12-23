#pragma once
#include "Game.h"
#include "Game.h"

class RouteHandler
{
public:
	RouteHandler();
	RouteHandler(const Game& game);


	bool checkEnteredMessage(const std::string& message);
	void addPlayer(PlayerPtr newPlayer);

private:
	Game m_game;

};

