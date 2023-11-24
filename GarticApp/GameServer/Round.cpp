#include "Round.h"

Round::Round(std::vector<SubRound*> subRounds) : m_subRounds{ subRounds }
{
}

int Round::GetSizeOfRound()
{
	return m_subRounds[0]->GetSizeOfPlayers();
}

void Round::ResetStatus()
{
	for (Player* player : m_players)
		player->SetPlayerStatus(false);
}

bool Round::RoundIsOver()
{
	uint16_t contor = 0;
	for (Player* player : m_players)
		if (player->GetPlayerStatus() == true)
			contor++;
	if (contor == m_players.size())
	{
		ResetStatus();
		return true;
	}
	return false;


}
