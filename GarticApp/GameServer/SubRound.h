#pragma once
#include <vector>
class SubRound
{
public:
	SubRound(Player* player, const std::string& word);
	void SeeWord(const std::string& word);
	bool GuessWord(const std::string& word);
	std::string SelectRandomWord(); // cuvintele ar trebui preluate din baza de date, dar deocamdata incerc sa implementez
	void ShowLetters(std::string& word);
	void StartRound();
	int GetSecond();
	void ChoosePainter(std::vector<Player*>& players);
	void CalculateScore(Player* player, const std::string& word);
	bool HaveAllPlayersGuessed();
	bool HasSubRoundEnded();
	int GetSizeOfPlayers();

private:
	std::vector<Player*> m_player;
	int m_counterGuessingPlayers;
	std::string m_word;
	int m_duration;
	bool m_hasTimeEnded;
	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
};

