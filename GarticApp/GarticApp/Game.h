#pragma once
#include "Player.h"
#include<vector>
#include "Round.h"
#include<map>
class Game
{
private:
	std::vector<Player*>m_players;
	std::map<Player*, int>m_leaderboard;
	std::vector<Round*>m_rounds;

public:
	Game(std::vector<Player*>players, std::map<Player*, int>leaderboard, std::vector<Round*>rounds);
	std::vector<Player*> GetPlayers() const;
	std::vector<Round*>GetRounds()const;
	void addPlayer(Player* player);
	void addRound(Round* round);
	std::map<Player*, int>GetLeaderboard()const;
	~Game();

};


