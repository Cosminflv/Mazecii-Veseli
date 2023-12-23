#pragma once
#include "Player.h"
#include "SubRound.h"
#include <vector>

using SubRoundPtr = std::shared_ptr<class SubRound>;

class Round
{
public:
	Round();
	Round(const std::vector<PlayerPtr>& players);
	Round(SubRoundPtr subRound, const int numberOfPlayers);
	
	void CreateSubRound(const std::vector<PlayerPtr>& players);

	int GetSizeOfRound() const;
	void ResetStatus(std::vector<PlayerPtr>& players) const;
	bool RoundIsOver(std::vector<PlayerPtr>& players) const;

private:
	SubRoundPtr m_subRound;
	int m_numberOfPlayers;
};

