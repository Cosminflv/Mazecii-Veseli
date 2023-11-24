#pragma once
#include "Player.h"
#include "SubRound.h"
#include <vector>

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

