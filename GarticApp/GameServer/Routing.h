#pragma once
#include "GameData.h"
#include "RouteHandler.h"
class Routing
{
public:
	Routing(GameStorage& storage);
	void Run();
private:
	crow::SimpleApp m_app;
	RouteHandler m_routeHandler;
	GameStorage m_storage;
};

