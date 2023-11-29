#pragma once
#include <vector>

using PlayerPtr = std::shared_ptr<class Player>;

class SubRound
{
public:
	std::string SelectRandomWord() const; // cuvintele ar trebui preluate din baza de date, dar deocamdata incerc sa implementez
	//cuvantul returnat din SelectRandowWord va fi transmis prin parametru in restul functiilor de mai jos
	SubRound();
	SubRound(const std::string& word, int numberOfPlayers);
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
	int m_counterGuessingPlayers;
	int m_numberOfPlayers;
	std::string m_word;
	int m_duration;
	bool m_hasTimeEnded;
	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
};

