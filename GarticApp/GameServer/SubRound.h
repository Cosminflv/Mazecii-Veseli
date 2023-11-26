#pragma once
#include <vector>

using PlayerPtr = std::shared_ptr<class Player>;

class SubRound
{
public:
	SubRound(const std::string& word, int numberOfPlayers);
	void SeeWord(const std::string& word);
	bool GuessWord(const std::string& word);
	std::string SelectRandomWord(); // cuvintele ar trebui preluate din baza de date, dar deocamdata incerc sa implementez
	void ShowLetters(std::string& word);
	void StartRound();
	int GetSecond();
	void ChoosePainter(std::vector<Player*>& players);
	void CalculateScore(const PlayerPtr& player, const std::string& word, const std::vector<PlayerPtr>& opponents);
	bool HaveAllPlayersGuessed();
	bool HasSubRoundEnded();
	int getNumberOfPlayers() const;

private:
	int m_counterGuessingPlayers;
	int m_numberOfPlayers;
	std::string m_word;
	int m_duration;
	bool m_hasTimeEnded;
	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
};

