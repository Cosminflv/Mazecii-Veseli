#pragma once 
#include "Player.h"
#include "Round.h"
#include "Chat.h"


#include <vector>
#include <map>

using PlayerPtr = std::shared_ptr<class Player>;
using RoundPtr = std::shared_ptr<class Round>;

class Game
{
public:
	Game(std::vector<PlayerPtr>players, std::map<PlayerPtr, int> leaderboard);
	Game();
	std::vector<PlayerPtr> GetPlayers() const;
	RoundPtr GetRound() const;
	Chat GetChat() const;
	bool CheckUniquePlayerUsername(PlayerPtr player) const;
	void AddPlayer(PlayerPtr player);
	std::map<PlayerPtr, int>GetLeaderboard() const;
	void PlayRound();
	void StartGame();
	void EndGame();
	void ResetGame();
	void UpdateLeaderboard();
	~Game();

private:
	std::vector<PlayerPtr>m_players;
	std::map<PlayerPtr, int>m_leaderboard;
	RoundPtr m_currRound;
	Chat m_gameChat;
};

