#pragma once
#include <vector>
#include "Timer.h"
#include "GameData.h"

using PlayerPtr = std::shared_ptr<class Player>;

class SubRound
{
public:
	SubRound();
	SubRound(const std::vector<PlayerPtr>& players);
	SubRound(const SubRound& r);
	SubRound(const std::string& word, int numberOfPlayers, Storage storage);

	//Getters
	Storage getStorage() const;
	int getCounterGuessingPlayers() const;
	int getNumberOfPlayers() const;
	std::string getWord() const;
	int getDuration() const;
	bool getHasTimeEnded() const;


    std::string SelectRandomWord(uint16_t difficulty); 
	std::string HideWord(const std::string& word);
	void SeeWord(const std::string& word) const;
	bool GuessWord(const std::string& word) const;
	void ShowLetters(std::string& word) const;
	void StartRound();
	void StopRound();
	int GetSecond();
	void ChoosePainter(std::vector<Player*>& players);
	void CalculateScore(const PlayerPtr& player, const std::string& word, const std::vector<PlayerPtr>& opponents);
	bool HaveAllPlayersGuessed() const;
	bool HasSubRoundEnded() const;

private:
    Storage m_storage;
	int m_counterGuessingPlayers;
	int m_numberOfPlayers;
	std::string m_word;
	int m_duration;
	bool m_hasTimeEnded;
	Timer m_timer;
};

