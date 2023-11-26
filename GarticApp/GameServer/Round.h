#pragma once
#include "Player.h"
#include "SubRound.h"
#include <vector>

class Round
{
public:
	Round(std::vector<SubRound*>subRounds, const int numberOfPlayers);
	int GetSizeOfRound() const;
	void ResetStatus(std::vector<PlayerPtr>& players) const;
	bool RoundIsOver(std::vector<PlayerPtr>& players) const;

private:
	std::vector<SubRound*>m_subRounds;
	int m_numberOfPlayers;
};

