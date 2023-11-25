﻿#include "Round.h"
#include "SubRound.h"
#include <iostream>
#include <string>
#include <random>

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

//aici trebuie sa ma folosesc codul lui Cosmin
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


void SubRound::CalculateScore(Player* player, const std::string& word, const std::vector<Player*>& opponents)
{
	player->GetRole();
	if (player->GetRole() == PlayerRole::Guesser)
	{
		bool hasGuessedCorrectly = false;
		if (player->GetRole() == PlayerRole::Guesser)
		{
			while (SubRound::GetSecond() < m_duration && !hasGuessedCorrectly)
			{
				if (SubRound::GuessWord(word))
				{
					hasGuessedCorrectly = true;
					std::cout << "Guessed at second: " << SubRound::GetSecond() << std::endl; //de modificat cu timer-ul din DLL
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
	if (player->GetRole() == PlayerRole::Painter)
	{
		SeeWord(word);
		double opponentsAverageTime = 0.0;
		int numOpponents = 0;

		for (const Player* opponent : opponents)
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


std::string SubRound::SelectRandomWord()
{
	std::string words[] = { "cuvinte", "din", "baza", "de", "date" }; // de modificat pentru a fi preluate cuvintele din Baza de Date
	int numWords = sizeof(words) / sizeof(words[0]);
	srand(static_cast<unsigned int>(time(nullptr)));
	int randomIndex = rand() % numWords;
	return words[randomIndex];
}

void SubRound::ShowLetters(std::string& word)
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