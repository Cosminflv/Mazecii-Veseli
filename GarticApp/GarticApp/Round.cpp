#include "Round.h"

Round::Round(Player* player, std::string word) : m_player(player), m_word(word)
{
	m_duration = 60;
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


