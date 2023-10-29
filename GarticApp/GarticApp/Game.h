#pragma once
#include "Player.h"
#include<vector>
#include "Round.h"
#include<map>
class Game
{
private:
	std::vector<Player*>m_players;
	std::map<Player*, int>m_clasament;
	std::vector<Round*>m_rounds;

public:
	Game(std::vector<Player*>players, std::map<Player*, int>clasament, std::vector<Round*>rounds);
	~Game();
};


