#include "Game.h"

Game::Game(std::vector<Player*> players, std::map<Player*, int> clasament, std::vector<Round*> rounds):
	m_players(players),
	m_clasament(clasament),
	m_rounds(rounds)
{
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
	for (auto& entry : m_clasament)
	{
		delete entry.first; 
	}
}
