#pragma once
#include "SubRound.h"
#include "Game.h"

class RouteHandler
{
public:
	RouteHandler();
	RouteHandler(const SubRound& subRound);


	bool checkEnteredMessage(const std::string& message);
private:
	SubRound m_subRound;

};

