#include "Round.h"

Round::Round()
{
	SubRoundPtr newSubRound = std::make_shared<SubRound>();
	m_subRound = newSubRound;
}

Round::Round(const std::vector<PlayerPtr>& players)
{
	m_numberOfPlayers = players.size();
	SubRoundPtr newSubRound = std::make_shared<SubRound>(players);
	m_subRound = newSubRound;
}

Round::Round(SubRoundPtr subRound, int numberOfPlayers) : m_subRound{ subRound }, m_numberOfPlayers{ numberOfPlayers }
{
	// Empty
}

void Round::CreateSubRound(const std::vector<PlayerPtr>& players)
{
	SubRoundPtr newSubRound = std::make_shared<SubRound>(players);
	m_subRound = newSubRound;
}

SubRoundPtr Round::GetSubround() const
{
	return m_subRound;
}

int Round::GetSizeOfRound() const
{
	return m_subRound->GetNumberOfPlayers();
}

void Round::ResetStatus(std::vector<PlayerPtr>& players) const
{
	for (PlayerPtr player : players)
		player->SetPlayerStatus(false);
}

bool Round::RoundIsOver(std::vector<PlayerPtr>& players) const
{
	uint16_t contor = 0;
	for (PlayerPtr player : players)
		if (player->GetPlayerStatus() == true)
			contor++;
	if (contor == players.size())
	{
		ResetStatus(players);
		return true;
	}
	return false;
}
