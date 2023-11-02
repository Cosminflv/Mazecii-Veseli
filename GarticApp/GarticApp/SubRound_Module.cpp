module SubRound;
using garticApp::mSubRound;
using garticApp::mPlayer;
using garticApp::mPlayerRole;

mSubRound::mSubRound(mPlayer* player, std::string word) : m_player(player), m_word(word)
{
	m_duration = 60;
}

void mSubRound::SeeWord(std::string word)
{
	std::cout << "Your word is: " << word;
}

bool mSubRound::GuessWord(std::string word)
{
	std::cout << "Enter your word: ";
	std::string enterWord;
	std::getline(std::cin, enterWord);
	return enterWord == word;
}
void mSubRound::StartRound()
{
	m_startTime = std::chrono::steady_clock::now();
}

int mSubRound::GetSecond()
{
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_startTime);
	return static_cast<int>(elapsedTime.count());
}

void mSubRound::CalculateScore(mPlayer* player, std::string word)
{
	bool hasGuessedCorrectly = false;
	player->GetRole();

	if (player->GetRole() == mPlayerRole::Painter)
	{
		SeeWord(word);
	}
	else if (player->GetRole() == mPlayerRole::Guesser)
	{
		while (mSubRound::GetSecond() < m_duration && !hasGuessedCorrectly)
		{
			if (mSubRound::GuessWord(word))
			{
				hasGuessedCorrectly = true;
				std::cout << "Guessed at second: " << mSubRound::GetSecond() << std::endl;
				if (mSubRound::GetSecond() < m_duration / 2)
					player->SetScore(100);
				else
				{
					int score = static_cast<int>(std::round(((60.0 - mSubRound::GetSecond()) * 100) / 30));
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


