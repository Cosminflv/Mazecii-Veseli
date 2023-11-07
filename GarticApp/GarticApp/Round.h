#pragma once
#include "SubRound.h"
#include "Player.h"
class Round
{
public:
	Round(std::vector<SubRound*>subRounds);
	int GetSizeOfRound();
	void ResetStatus();
	bool RoundIsOver();

private:
	std::vector<SubRound*>m_subRounds;
	std::vector<Player*>m_players;
};

