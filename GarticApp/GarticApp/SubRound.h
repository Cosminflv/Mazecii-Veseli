#pragma once
#include <chrono>
#include <thread>
#include <string>
#include <random>
#include <iostream>
#include "Player.h"
class SubRound
{
public:
	SubRound(std::vector<Player*> players, std::string word);
	void SeeWord(std::string word);
	bool GuessWord(std::string word);
	void StartSubround();
	int GetSecond();
	void ChoosePainter(std::vector<Player*>& players);
	void CalculateScore(std::vector<Player*> players, std::string word);
	bool HaveAllPlayersGuessed();
	bool HasSubRoundEnded();
	int GetSizeOfPlayers();
private:
	std::vector<Player*> m_players;
	int m_counterGuessingPlayers; //RENAME TO PAINTER
	std::string m_word;
	int m_duration;
	bool m_hasTimeEnded;
	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
};

