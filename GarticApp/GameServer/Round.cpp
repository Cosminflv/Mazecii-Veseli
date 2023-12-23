#include "Round.h"

Round::Round(SubRoundPtr subRound, int numberOfPlayers) : m_subRound{ subRound }, m_numberOfPlayers{ numberOfPlayers }
{
}

int Round::GetSizeOfRound() const
{
	return m_subRound->getNumberOfPlayers();
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
