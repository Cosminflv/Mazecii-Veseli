#pragma once
#include "SubRound.h"

class Round
{
public:
	Round(std::vector<SubRound>subRounds);
	int GetSizeOfRound();
private:
	std::vector<SubRound>m_subRounds;
};

