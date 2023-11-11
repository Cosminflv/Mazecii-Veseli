module round;
using garticApp::mPlayer;
using garticApp::mSubRound;
using garticApp::mRound;

mRound::mRound(std::vector<mSubRound*> subRounds) : m_subRounds{ subRounds }
{
}

int mRound::GetSizeOfRound()
{
	return m_subRounds[0]->GetSizeOfPlayers();
}

void mRound::ResetStatus()
{
	for (mPlayer* player : m_players)
		player->SetPlayerStatus(false);
}

bool mRound::RoundIsOver()
{
	uint16_t contor = 0;
	for (mPlayer* player : m_players)
		if (player->GetPlayerStatus() == true)
			contor++;
	if (contor == m_players.size())
	{
		ResetStatus();
		return true;
	}
	return false;


}
