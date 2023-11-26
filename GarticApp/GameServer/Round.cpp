#include "Round.h"

Round::Round(std::vector<SubRound*> subRounds, int numberOfPlayers) : m_subRounds{ subRounds }, m_numberOfPlayers{ numberOfPlayers }
{
}

int Round::GetSizeOfRound()
{
	return m_subRounds[0]->getNumberOfPlayers();
}

void Round::ResetStatus(std::vector<PlayerPtr>& players)
{
	for (PlayerPtr player : players)
		player->SetPlayerStatus(false);
}

bool Round::RoundIsOver(std::vector<PlayerPtr>& players)
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
