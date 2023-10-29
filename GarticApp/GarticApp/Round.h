#pragma once
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include "Player.h"
class Round
{
	Round(std::vector<Player*> players, std::string word, int duration);
	void SeeWord(std::string word);
	bool GuessWord(std::string word);
	void StartRound();
	int GetSecond();
private:
	std::string m_word;
	int duration;
	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
};

