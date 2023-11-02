#include "Game.h"

Game::Game(std::vector<Player*> players, std::map<Player*, int> leaderboard, std::vector<SubRound*> rounds):
	m_players(players),
	m_leaderboard(leaderboard),
	m_rounds(rounds)
{
}

Game::Game()
{
	
}


std::vector<Player*> Game::GetPlayers() const
{
	return m_players;
}

std::vector<SubRound*> Game::GetRounds() const
{
	return m_rounds;
}

std::map<Player*, int>Game::GetLeaderboard() const
{
	return m_leaderboard;
}
void Game::PlayRound()
{

}

void Game::UpdateLeaderboard()
{
	m_leaderboard.clear();
		for (SubRound* round : m_rounds) {
			for (Player* player : m_players) {
				int roundScore = player->GetScore();
				m_leaderboard[player] += roundScore;
			}
		}

}
void Game::AddPlayer(Player* player)
{
	m_players.push_back(player);
}

void Game::AddRound(SubRound* round)
{
	m_rounds.push_back(round);
}

Game::~Game()
{
	m_players.clear();
	m_rounds.clear();
	m_leaderboard.clear();
}
