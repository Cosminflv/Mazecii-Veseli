#pragma once
#include "GameData.h"
#include "Game.h"
#include "RouteHandler.h"

class Routing
{
public:
	Routing(GameStorage& storage, std::unique_ptr<Game> game);
	void Run();
private:
	crow::SimpleApp m_app;
	RouteHandler m_routeHandler;
	GameStorage m_storage;
};

