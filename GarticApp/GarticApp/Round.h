#pragma once
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include "Player.h"
class Round
{
public:
	Round(Player* player, std::string word);
	void SeeWord(std::string word);
	bool GuessWord(std::string word);
	void StartRound();
	int GetSecond();
	void CalculateScore(Player* player, std::string word);
private:
	std::string m_word;
	int m_duration;
	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
};

