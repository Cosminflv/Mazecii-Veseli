#pragma once
#include <vector>
#include "Timer.h"
#include "GameData.h"

using PlayerPtr = std::shared_ptr<class Player>;

class SubRound
{
public:
    std::string SelectRandomWord(uint16_t difficulty); 
	SubRound();
	SubRound(const std::string& word, int numberOfPlayers, Storage storage);
	void SeeWord(const std::string& word) const;
	bool GuessWord(const std::string& word) const;
	void ShowLetters(std::string& word) const;
	void StartRound();
	int GetSecond() const;
	void ChoosePainter(std::vector<Player*>& players);
	void CalculateScore(const PlayerPtr& player, const std::string& word, const std::vector<PlayerPtr>& opponents) const;
	bool HaveAllPlayersGuessed() const;
	bool HasSubRoundEnded() const;
	int getNumberOfPlayers() const;

private:
    Storage m_storage;
	int m_counterGuessingPlayers;
	int m_numberOfPlayers;
	std::string m_word;
	int m_duration;
	bool m_hasTimeEnded;
	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
};

