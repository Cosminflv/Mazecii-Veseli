#pragma once
#include "GameData.h"
#include "Game.h"
#include "RouteHandler.h"
#include <set>

class Routing
{
public:
	Routing(GameStorage& storage, std::unique_ptr<Game> game);
	void Run();
private:
	crow::SimpleApp m_app;
	RouteHandler m_routeHandler;
	GameStorage m_storage;
	std::vector<std::pair<int, int>> m_receivedCoordinates;
	std::vector<std::pair<std::string, int>> m_receivedInfo;
	std::set<std::string> m_codes;
};

