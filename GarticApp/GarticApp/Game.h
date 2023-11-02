#pragma once
#include "Player.h"
#include<vector>
#include "SubRound.h"
#include<map>
class Game
{
private:
	std::vector<Player*>m_players;
	std::map<Player*, int>m_leaderboard;
	std::vector<SubRound*>m_rounds;

public:
	Game(std::vector<Player*>players, std::map<Player*, int>leaderboard, std::vector<SubRound*>rounds);
	Game();
	std::vector<Player*> GetPlayers() const;
	std::vector<SubRound*>GetRounds()const;
	void AddPlayer(Player* player);
	//no need to add rounds during a game,
	//the number of rounds is given by the number of players
	void AddRound(SubRound* round);
	std::map<Player*, int>GetLeaderboard()const;
	void PlayRound();
	void StartGame();
	void UpdateLeaderboard();
	~Game();

};


