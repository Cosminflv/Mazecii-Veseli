#pragma once 
#include "Player.h"
#include "Round.h"
//#include "Timer.h"

#include <vector>
#include <map>

using PlayerPtr = std::shared_ptr<class Player>;
using RoundPtr = std::shared_ptr<class Round>;

class Game
{
public:
	Game(std::vector<PlayerPtr>players, std::map<PlayerPtr, int> leaderboard, std::vector<RoundPtr> rounds);
	Game();
	std::vector<PlayerPtr> GetPlayers() const;
	std::vector<RoundPtr>GetRounds() const;
	bool CheckUniquePlayerUsername(PlayerPtr player);
	void AddPlayer(PlayerPtr player);
	//no need to add rounds during a game,
	//the number of rounds is given by the number of players
	void AddRound(RoundPtr round);
	std::map<PlayerPtr, int>GetLeaderboard()const;
	void PlayRound();
	void StartGame();
	void EndGame();
	void ResetGame();
	void UpdateLeaderboard();
	~Game();

private:
	std::vector<PlayerPtr>m_players;
	std::map<PlayerPtr, int>m_leaderboard;
	std::vector<RoundPtr>m_rounds;
	//Timer m_timer;
};

