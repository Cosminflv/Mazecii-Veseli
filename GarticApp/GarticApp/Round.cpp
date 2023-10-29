#include "Round.h"
#include <vector>

Round::Round(std::vector<Player*> players, std::string word, int duration)
	: duration(60)
{
	for (int i = 0; i < players.size(); i++)
	{
		players[i]->GetRole();
		if (players[i]->GetRole() == PlayerRole::Painter)
		{
			SeeWord(word);
		}
		else if (players[i]->GetRole() == PlayerRole::Guesser)
		{
			while (Round::GetSecond() < duration)
			{
				if (Round::GuessWord(word))
				{
					std::cout << "Guessed at second: " << Round::GetSecond() << std::endl;
					if (Round::GetSecond() < duration / 2)
						players[i]->SetScore(100);
					else
					{
						int score = static_cast<int>(std::round(((60.0 - Round::GetSecond()) * 100) / 30));
						players[i]->SetScore(score);
					}
				}
				else if (!Round::GuessWord(word))
					players[i]->SetScore(-50);				
			}
		}
	}
}

void Round::SeeWord(std::string word)
{
	std::cout << "Your word is: " << word;
}

bool Round::GuessWord(std::string word)
{
	std::cout << "Enter your word: ";
	std::string enterWord;
	std::getline(std::cin, enterWord);
	return enterWord == word;
}

void Round::StartRound()
{
	m_startTime = std::chrono::steady_clock::now();
}

int Round::GetSecond()
{
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_startTime);
	return static_cast<int>(elapsedTime.count());
}


