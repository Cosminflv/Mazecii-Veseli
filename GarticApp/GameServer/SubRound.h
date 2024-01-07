#pragma once
#include <vector>
#include "Timer.h"
#include "GameData.h"
#include <chrono>;
#include <thread>;

using PlayerPtr = std::shared_ptr<class Player>;

class SubRound
{
public:
	SubRound();
	SubRound(const std::vector<PlayerPtr>& players);
	SubRound(const SubRound& r);
	SubRound(const std::string& word, int numberOfPlayers, Storage storage);

	//Getters
	Storage GetStorage() const;
	int GetCounterGuessingPlayers() const;
	int GetNumberOfPlayers() const;
	std::string GetWord() const;
	int GetDuration() const;
	bool GetHasTimeEnded() const;

    std::string SelectRandomWord(uint16_t difficulty); 
	std::string HideWord(const std::string& word);
	std::string UpdateWordWithLetters(std::string& seenWord, std::string& currentWord);
	void SetHiddenWord(std::string& word);
	std::string GetHiddentWord();
	void SetSeenWord(std::string& word);
	std::string GetSeenWord();

	void SeeWord(const std::string& word) const;
	bool GuessWord(const std::string& word) const;
	void StartRound();
	void StopRound();

	void ChoosePainter(std::vector<Player*>& players);
	bool HaveAllPlayersGuessed() const;
	bool HasSubRoundEnded() const;
	void MakeAllLettersFalse(const std::string& sizeWord);

private:
    Storage m_storage;
	int m_counterGuessingPlayers;
	int m_numberOfPlayers;
	std::string m_seenWord;
	std::string m_hiddenWord;
	std::vector<bool>m_letterShown;
	int m_counterLetters;
	int m_duration;
	bool m_hasTimeEnded;
	Timer m_timer;
	
};

