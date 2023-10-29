#include "Game.h"

Game::Game(std::vector<Player*> players, std::map<Player*, int> leaderboard, std::vector<Round*> rounds):
	m_players(players),
	m_leaderboard(leaderboard),
	m_rounds(rounds)
{
}


std::vector<Player*> Game::GetPlayers() const
{
	return m_players;
}

std::vector<Round*> Game::GetRounds() const
{
	return m_rounds;
}

std::map<Player*, int>Game::GetLeaderboard() const
{
	return m_leaderboard;
}
void Game::addPlayer(Player* player)
{
	m_players.push_back(player);
}

void Game::addRound(Round* round)
{
	m_rounds.push_back(round);
}

Game::~Game()
{
	for (Player* player : m_players)
	{
		delete player;
	}
	for (Round* round : m_rounds)
	{
		delete round;
	}
	for (auto& entry : m_leaderboard)
	{
		delete entry.first; 
	}
}
