﻿#include "Round.h"
#include "SubRound.h"
#include <iostream>
#include <string>
#include <random>


SubRound::SubRound() :
	m_counterGuessingPlayers(0),
	m_numberOfPlayers(0),
	m_word(""),
	m_duration(0),
	m_hasTimeEnded(false),
	m_timer(1),
	m_storage(createStorage("Database.sqlite")) // initial e createEmptyStorage
{
}

SubRound::SubRound(const std::string& word, const int numberOfPlayers, Storage storage)
	: m_word{ word },
	m_numberOfPlayers{ numberOfPlayers },
	m_storage(storage),
	m_timer(1)
{
	m_duration = 60;
}
void SubRound::SeeWord(const std::string& word) const
{
	std::cout << "Your word is: " << word;
}

bool SubRound::GuessWord(const std::string& word) const
{
	std::cout << "Enter your word: ";
	std::string enterWord;
	std::getline(std::cin, enterWord);
	return enterWord == word;
}

void SubRound::StartRound()
{
	m_timer.StartTimer();
}

void SubRound::StopRound()
{
	m_timer.StopTimer();
}


std::string SubRound::SelectRandomWord(uint16_t difficulty)
{
	auto filteredWords = m_storage.select(&Word::description, sql::where(sql::c(&Word::difficulty) == difficulty));
	if (filteredWords.empty())
	{
		std::cerr << "There are no words with the selected difficulty.\n";
		return "";
	}
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	auto randomIndex = std::rand() % filteredWords.size();
	return filteredWords[randomIndex];
}

//aici trebuie sa ma folosesc codul lui Cosmin
int SubRound::GetSecond()
{
	auto milliseconds = m_timer.GetRemainingTime();
	int seconds = static_cast<int>(milliseconds.count()) / 1000;
	return seconds;
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


void SubRound::CalculateScore(const PlayerPtr& player, const std::string& word, const std::vector<PlayerPtr>& opponents)
{
	player->GetRole();
	if (player->GetRole() == PlayerRole::Guesser)
	{
		bool hasGuessedCorrectly = false; 
		if (player->GetRole() == PlayerRole::Guesser)
		{
			while (GetSecond() < m_duration && !hasGuessedCorrectly)
			{
				if (SubRound::GuessWord(word))
				{
					hasGuessedCorrectly = true;
					std::cout << "Guessed at second: " << GetSecond() << std::endl; //de modificat cu timer-ul din DLL
					if (GetSecond() < m_duration / 2)
						player->SetScore(100);
					else
					{
						int score = static_cast<int>(std::round(((60.0 - GetSecond()) * 100) / 30));
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
	if (player->GetRole() == PlayerRole::Painter)
	{
		SeeWord(word);
		double opponentsAverageTime = 0.0;
		int numOpponents = 0;

		for (const PlayerPtr opponent : opponents)
		{
			if (opponent->GetRole() == PlayerRole::Guesser && opponent->GetScore() == 100)
			{
			//	opponentsAverageTime += opponent.GetSecond();
				numOpponents++;
				//DE GANDIT MAI BINE CUM POATE FI ACEASTA FUNCTIE IMPLEMENTATA
			}
		}
		if (numOpponents > 0)
		{
			opponentsAverageTime /= numOpponents;

			int painterScore = static_cast<int>(std::round(((60.0 - opponentsAverageTime) * 100) / 60));
			player->SetScore(painterScore);
		}
		else
		{
			// Nu există adversari care au ghicit corect
			player->SetScore(-100);
		}
	}
}


void SubRound::ShowLetters(std::string& word) const
{
	int sizeOfWord = word.size();
	int maxLettersToShow = sizeOfWord / 2;
	std::string displayWord(sizeOfWord, '_');
	std::cout << "Ghiceste cuvantul: " << displayWord << std::endl;
	for (int i = 0; i < maxLettersToShow; ++i) {
		std::this_thread::sleep_for(std::chrono::seconds(30)); //de modificat pentru a fi pus timer-ul general.
		int randomIndex = rand() % sizeOfWord;
		displayWord[randomIndex] = word[randomIndex];
		std::cout << "Litera " << i + 1 << ": " << displayWord << std::endl;
	}
}

bool SubRound::HaveAllPlayersGuessed() const
{
	if (m_counterGuessingPlayers == m_numberOfPlayers - 1)
		return true;
	return false;
}

bool SubRound::HasSubRoundEnded() const
{
	if (HaveAllPlayersGuessed() == true)
		return true;
	else if (m_hasTimeEnded == true)
		return true;
	return false;
}

int SubRound::getNumberOfPlayers() const
{
	return m_numberOfPlayers;
}
