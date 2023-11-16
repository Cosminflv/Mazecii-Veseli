module Game;
using garticApp::Player;
using garticApp::Round;
using garticApp::Game;

Game::Game(std::vector<Player*> players, std::map<Player*, int> leaderboard, std::vector<Round*> rounds) :
	m_players{ players },
	m_leaderboard{ leaderboard }

{
	m_rounds.resize(4);
}

Game::Game()
{

}


std::vector<Player*> Game::GetPlayers() const
{
	return m_players;
}

std::vector<Round*> Game::GetRounds() const
{
	return m_rounds;
}

bool Game::CheckUniquePlayerUsername(Player* player)
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

std::map<Player*, int>Game::GetLeaderboard() const
{
	return m_leaderboard;
}
void Game::PlayRound()
{

}

void Game::StartGame()
{
}

void Game::EndGame()
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

void Game::ResetGame()
{
	for (Player* player : m_players)
		player->SetScore(0);
	m_rounds.clear();
}

void Game::UpdateLeaderboard()
{
	m_leaderboard.clear();
	for (Round* round : m_rounds) {
		for (Player* player : m_players) {
			int roundScore = player->GetScore();
			m_leaderboard[player] += roundScore;
		}
	}

}
void Game::AddPlayer(Player* player)
{
	m_players.push_back(player);
}

void Game::AddRound(Round* round)
{
	m_rounds.push_back(round);
}

Game::~Game()
{
	m_players.clear();
	m_rounds.clear();
	m_leaderboard.clear();
}
