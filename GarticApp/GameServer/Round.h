#pragma once
#include "Player.h"
#include "SubRound.h"
#include <vector>

class Round
{
public:
	Round(std::vector<SubRound*>subRounds, const int numberOfPlayers);
	int GetSizeOfRound();
	void ResetStatus(std::vector<PlayerPtr>& players);
	bool RoundIsOver(std::vector<PlayerPtr>& players);

private:
	std::vector<SubRound*>m_subRounds;
	int m_numberOfPlayers;
};

