#pragma once
#include "GameData.h"

class Routing
{
public:
	void Run(GameStorage& storage);
private:
	crow::SimpleApp m_app;
};

