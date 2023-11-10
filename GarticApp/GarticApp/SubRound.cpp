#include "SubRound.h"

SubRound::SubRound(std::vector<Player*> players, std::string word) 
	: m_players{ players }, m_word{ word }, m_counterGuessingPlayers{ 0 }, m_hasTimeEnded{ false }
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
void SubRound::StartSubround()
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
	// Inițializează generatorul de numere aleatoare
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	std::vector<Player*> availablePainters;
	for (Player* player : players)
	{
		if (!player->GetPlayerStatus())
			availablePainters.push_back(player);
	}
	if (availablePainters.empty())
	{
		std::cout << "Au desenat toti jucatorii. Runda s-a terminat!";
		return;
	}

	Player* selectedPainter = availablePainters[std::rand() % availablePainters.size()];
	int indice=std::distance(players.begin(), std::find(players.begin(), players.end(), selectedPainter));
	players[indice]->SetPlayerStatus(true);
	std::cout << selectedPainter << " deseneaza!";
}

void SubRound::CalculateScore(std::vector<Player*> players, std::string word)
{
	for (int i = 0; i < players.size(); i++)
	{
		bool hasGuessedCorrectly = false;
		players[i]->GetRole();

		if (players[i]->GetRole() == PlayerRole::Painter)
		{
			SeeWord(word);
		}
		else if (players[i]->GetRole() == PlayerRole::Guesser)
		{
			while (SubRound::GetSecond() < m_duration && !hasGuessedCorrectly)
			{
				if (SubRound::GuessWord(word))
				{
					hasGuessedCorrectly = true;
					m_counterGuessingPlayers++;
					players[i]->SetPlayerStatus(true);
					std::cout << "Guessed at second: " << SubRound::GetSecond() << std::endl;
					if (SubRound::GetSecond() < m_duration / 2)
					{
						players[i]->SetScore(100);
					}
					else
					{
						int score = static_cast<int>(std::round(((60.0 - SubRound::GetSecond()) * 100) / 30));
						players[i]->SetScore(score);
					}
					break;
				}
			}
		}
		if (!hasGuessedCorrectly)
		{
			players[i]->SetScore(-50);
			m_hasTimeEnded = true;
		}
	}
}

bool SubRound::HaveAllPlayersGuessed()
{
	if (m_counterGuessingPlayers == m_players.size()-1)
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
	return m_players.size();
}


