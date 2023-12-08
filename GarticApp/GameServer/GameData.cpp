#include "GameData.h"

void populateStorage(Storage& storage)
{
	std::ifstream inputFile("wordsIn.txt");
	std::string word;
	std::vector<Word>words;
	uint16_t difficulty;
	while (inputFile >> word>>difficulty)
	{
		Word w{ -1,word,difficulty };
		words.push_back(w);
	}
	storage.insert_range(words.begin(), words.end());
}
