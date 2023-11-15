module SubRound;
using garticApp::SubRound;
using garticApp::Player;
using garticApp::PlayerRole;

SubRound::SubRound(Player* player, const std::string& word) : m_player{ player }, m_word{ word }
{
	m_duration = 60;
}

void SubRound::SeeWord(const std::string& word)
{
	std::cout << "Your word is: " << word;
}

bool SubRound::GuessWord(const std::string& word)
{
	std::cout << "Enter your word: ";
	std::string enterWord;
	std::getline(std::cin, enterWord);
	return enterWord == word;
}
void SubRound::StartRound()
{
	m_startTime = std::chrono::steady_clock::now();
}

int SubRound::GetSecond()
{
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_startTime);
	return static_cast<int>(elapsedTime.count());
}

void SubRound::ChoosePainter(std::vector<Player*>& players)
{
	if (players.empty()) {
		std::cout << "Vectorul de jucatori este gol.\n";
		return;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<std::size_t> dis(0, players.size() - 1);
	std::size_t index = dis(gen);
	players[index]->SetPlayerStatus(true);
	std::cout << players[index] << " deseneaza!";
}

void SubRound::CalculateScore(Player* player, const  std::string& word)
{
	bool hasGuessedCorrectly = false;
	player->GetRole();
	if (player->GetRole() == PlayerRole::Painter)
	{
		SeeWord(word);
	}
	else if (player->GetRole() == PlayerRole::Guesser)
	{
		while (SubRound::GetSecond() < m_duration && !hasGuessedCorrectly)
		{
			if (SubRound::GuessWord(word))
			{
				hasGuessedCorrectly = true;
				std::cout << "Guessed at second: " << SubRound::GetSecond() << std::endl;
				if (SubRound::GetSecond() < m_duration / 2)
					player->SetScore(100);
				else
				{
					int score = static_cast<int>(std::round(((60.0 - SubRound::GetSecond()) * 100) / 30));
					player->SetScore(score);
				}
				break;
			}
		}
	}
	if (!hasGuessedCorrectly)
	{
		player->SetScore(-50);
	}
}

bool SubRound::HaveAllPlayersGuessed()
{
	if (m_counterGuessingPlayers == m_player.size() - 1)
		return true;
	return false;
}

bool SubRound::HasSubRoundEnded()
{
	if (HaveAllPlayersGuessed() == true)
		return true;
	else if (m_hasTimeEnded == true)
		return true;
	return false;
}

int SubRound::GetSizeOfPlayers()
{
	return m_player.size();
}