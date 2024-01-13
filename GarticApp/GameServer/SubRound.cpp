#include "Round.h"
#include "SubRound.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <random>
#include <numeric>
#include <string_view>


SubRound::SubRound() :
	m_counterGuessingPlayers(0),
	m_numberOfPlayers(0),
	m_seenWord(""),
	m_duration(0),
	m_hasTimeEnded(false),
	m_timer(1),
	m_storage(createStorage("Database.sqlite")) // initial e createEmptyStorage
{
	// Empty
}

SubRound::SubRound(const std::vector<PlayerPtr>& players):
	m_counterGuessingPlayers(0),
	m_numberOfPlayers(players.size()),
	m_duration(0),
	m_hasTimeEnded(false),
	m_timer{1},
	m_storage(createStorage("Database.sqlite"))
{
	// Empty
}

SubRound::SubRound(const SubRound& r) : 
	m_storage {r.GetStorage()},
	m_counterGuessingPlayers {r.GetCounterGuessingPlayers()},
	m_duration {r.GetDuration()},
	m_hasTimeEnded {r.GetHasTimeEnded()},
	m_numberOfPlayers {r.GetNumberOfPlayers()},
	m_timer { 1 },
	m_seenWord {r.GetWord()}
{
	// Empty
}

SubRound::SubRound(const std::string& word, const int numberOfPlayers, Storage storage)
	: m_seenWord{ word },
	m_numberOfPlayers{ numberOfPlayers },
	m_storage(storage),
	m_timer(1)
{
	m_duration = 60;
}

SubRound::SubRound(const std::string& word, const int numberOfPlayers)
	: m_seenWord{word},
	m_numberOfPlayers{numberOfPlayers},
	m_storage{createStorage("Database.sqlite")},
	m_timer(1),
	m_duration(60)
{
}


void SubRound::SeeWord(const std::string& word) const
{
	std::cout << "Your word is: " << word;
}

bool SubRound::GuessWord(const std::string_view& word) const
{
	return m_seenWord == word;
}

void SubRound::StartRound()
{
	m_timer.StartTimer();
}

void SubRound::StopRound()
{
	m_timer.StopTimer();
}


std::string SubRound::SelectRandomWord(uint16_t difficulty)
{
	auto filteredWords = m_storage.select(&Word::description, sql::where(sql::c(&Word::difficulty) == difficulty));
	if (filteredWords.empty())
	{
		std::cerr << "There are no words with the selected difficulty.\n";
		return "";
	}
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	auto randomIndex = std::rand() % filteredWords.size();
	m_seenWord = filteredWords[randomIndex];
	size_t found = m_seenWord.find('_');
	while (found != std::string::npos)
	{
		m_seenWord.replace(found, 1, " ");
		found = m_seenWord.find('_', found + 1);
	}
	std::cout << "\nCuvantul filtrat fara _ si cu spatii este:\n" << m_seenWord;
	return filteredWords[randomIndex];
}

std::string SubRound::HideWord(const std::string& word)
{
	bool hasSpaces = std::any_of(word.begin(), word.end(), [](char c) { return c == ' ' || c == '_'; });
	std::string hiddenWord(word.length(), hasSpaces ? ' ' : '-');

	if (!hasSpaces)
	{
		MakeAllLettersFalse(word);
		m_counterLetters = 1;
	}
	else
	{
		m_counterLetters = 0;
	}

	return hiddenWord;
}


std::string SubRound::UpdateWordWithLetters(std::string& seenWord, std::string&currentWord)
{
	if (currentWord.size() == 0) {
		std::cerr << "Word string empty." << std::endl;
		return "";
	}
	int randomIndex=0;
	if (m_counterLetters<seenWord.size()/2)
	{
		do {
			randomIndex = rand() % currentWord.size();
		} while (m_letterShown[randomIndex]);

	m_letterShown[randomIndex] = true;
	currentWord[randomIndex] = seenWord[randomIndex];
	}
	m_counterLetters++;
	return currentWord;
}

void SubRound::SetHiddenWord(std::string& word)
{
	m_hiddenWord = word;
}

std::string SubRound::GetHiddentWord()
{
	return m_hiddenWord;
}

void SubRound::SetSeenWord(std::string_view word)
{
	m_seenWord = word;
}

std::string SubRound::GetSeenWord()
{
	return m_seenWord;
}

void SubRound::ChoosePainter(std::vector<PlayerPtr>& players)
{
	if (players.empty()) {
		std::cout << "Empty player vector.\n";
		return;
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<std::size_t> dis(0, players.size() - 1);
	std::size_t index = dis(gen);
	players[index]->SetPlayerStatus(true);
	std::cout << players[index] << " is drawing!";
}


bool SubRound::HaveAllPlayersGuessed() const
{
	return m_counterGuessingPlayers == m_numberOfPlayers - 1 ? true : false;
}

bool SubRound::HasSubRoundEnded() const
{
	return HaveAllPlayersGuessed() == true ? true : false;
}

bool SubRound::NoOneGuessed(const std::vector<PlayerPtr>& players)
{
	return std::all_of(players.begin(), players.end(),
		[](const PlayerPtr player) {
			return player->GetSecond() == 60;
		});
}

int SubRound::AverageSeconds(const std::vector<PlayerPtr>& players)
{
	if (players.empty()) return 0;

	auto sum = std::accumulate(players.begin(), players.end(), 0,
		[](int total, const PlayerPtr player) {
			return total + player->GetSecond();
		});

	return static_cast<int>(sum / players.size());
}

int SubRound::CalculatePainterScore(const std::vector<PlayerPtr>& players)
{
	int score = NoOneGuessed(players) ? -100 : ((60 - AverageSeconds(players)) * 100) / 60;
	return score;
}

void SubRound::MakeAllLettersFalse(const std::string& sizeWord)
{
	m_letterShown.resize(sizeWord.size(),false);
}

Storage SubRound::GetStorage() const
{
	return m_storage;
}

int SubRound::GetCounterGuessingPlayers() const
{
	return m_counterGuessingPlayers;
}

int SubRound::GetNumberOfPlayers() const
{
	return m_numberOfPlayers;
}

std::string SubRound::GetWord() const
{
	return m_seenWord;
}

int SubRound::GetDuration() const
{
	return m_duration;
}

bool SubRound::GetHasTimeEnded() const
{
	return m_hasTimeEnded;
}

std::vector<bool> SubRound::GetLetterShown() const
{
	return m_letterShown;
}