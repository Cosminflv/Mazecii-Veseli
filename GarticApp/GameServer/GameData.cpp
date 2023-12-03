#include "GameData.h"

void populateStorage(Storage& storage)
{
	std::ifstream inputFile("wordsIn.txt");
	std::string word;
	std::vector<Word>words;
	while (inputFile >> word)
	{
		Word w{ -1,word };
		words.push_back(w);
	}
	storage.insert_range(words.begin(), words.end());
}
