#pragma once 
#include "Player.h"
#include "Round.h"
#include "Chat.h"
#include "EGameStatus.h"

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
	Chat& GetChat() const;
	EGameStatus GetGameStatus() const;
	std::string GetGameStatusAsString() const;

	static EGameStatus EGameStatusFromString(const std::string& status);
	void SetGameStatus(const std::string& status);

	bool CheckUniquePlayerUsername(PlayerPtr player) const;
	bool IsCurrentRoundReset() const;
	void AddPlayer(PlayerPtr player);
	std::map<PlayerPtr, int>GetLeaderboard() const;

	void CreateRound(const std::vector<PlayerPtr>& players);

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
	mutable Chat m_gameChat;
	EGameStatus m_gameStatus;

};

