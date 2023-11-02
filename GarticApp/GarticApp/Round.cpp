#include "Round.h"

Round::Round(std::vector<SubRound> subRounds): m_subRounds(subRounds)
{
}

int Round::GetSizeOfRound()
{
	return m_subRounds[0].GetSizeOfPlayers();
}

