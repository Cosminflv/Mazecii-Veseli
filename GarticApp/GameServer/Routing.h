#pragma once
#include "GameData.h"
#include "Game.h"
#include "RouteHandler.h"
class Routing
{
public:
	Routing(GameStorage& storage);
	void Run(Game& game);
private:
	crow::SimpleApp m_app;
	RouteHandler m_routeHandler;
	GameStorage m_storage;
};

