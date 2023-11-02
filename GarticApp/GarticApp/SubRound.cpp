#include "SubRound.h"

SubRound::SubRound(Player* player, std::string word) : m_player(player), m_word(word)
{
	m_duration = 60;
}

void SubRound::SeeWord(std::string word)
{
	std::cout << "Your word is: " << word;
}

bool SubRound::GuessWord(std::string word)
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

void SubRound::CalculateScore(Player* player, std::string word)
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


