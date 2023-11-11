module game;
using garticApp::mPlayer;
using garticApp::mRound;
using garticApp::mGame;

mGame::mGame(std::vector<mPlayer*> players, std::map<mPlayer*, int> leaderboard, std::vector<mRound*> rounds) :
	m_players{ players },
	m_leaderboard{ leaderboard }

{
	m_rounds.resize(4);
}

mGame::mGame()
{

}


std::vector<mPlayer*> mGame::GetPlayers() const
{
	return m_players;
}

std::vector<mRound*> mGame::GetRounds() const
{
	return m_rounds;
}

bool mGame::CheckUniquePlayerUsername(mPlayer* player)
{
	std::set<std::string> setOfUsernames;
	for (auto player : m_players)
	{
		setOfUsernames.insert(player->GetUsername());
	}
	if (setOfUsernames.find(player->GetUsername()) != setOfUsernames.end())
	{
		return false; // username was found => not unique
	}
	return true; // username was unique
}

std::map<mPlayer*, int>mGame::GetLeaderboard() const
{
	return m_leaderboard;
}
void mGame::PlayRound()
{

}

void mGame::StartGame()
{
}

void mGame::EndGame()
{
	std::cout << "Jocul s-a incheiat!\n";
	//afisare clasament
	std::string choice;
	std::cout << "Doriti sa reluati jocul? (Da/Nu): ";
	std::cin >> choice;

	if (choice == "Da") {
		ResetGame();
		StartGame();
	}
	else {
		std::cout << "Jocul s-a incheiat.\n";
	}
}

void mGame::ResetGame()
{
	for (mPlayer* player : m_players)
		player->SetScore(0);
	m_rounds.clear();
}

void mGame::UpdateLeaderboard()
{
	m_leaderboard.clear();
	for (mRound* round : m_rounds) {
		for (mPlayer* player : m_players) {
			int roundScore = player->GetScore();
			m_leaderboard[player] += roundScore;
		}
	}

}
void mGame::AddPlayer(mPlayer* player)
{
	m_players.push_back(player);
}

void mGame::AddRound(mRound* round)
{
	m_rounds.push_back(round);
}

mGame::~mGame()
{
	m_players.clear();
	m_rounds.clear();
	m_leaderboard.clear();
}
