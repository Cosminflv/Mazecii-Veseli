#include "GameData.h"
//
//void populateStorage(Storage& storage)
//{
//	std::ifstream inputFile("wordsIn.txt");
//	std::string word;
//	std::vector<Word>words;
//	uint16_t difficulty;
//	while (inputFile >> word>>difficulty)
//	{
//		Word w{ -1,word,difficulty };
//		words.push_back(w);
//	}
//	storage.insert_range(words.begin(), words.end());
//}

bool GameStorage::Initialize()
{
	m_db.sync_schema();
	auto initWordsCount = m_db.count<Word>();
	if (initWordsCount == 0)
		PopulateStorage();
	auto wordsCount = m_db.count<Word>();
	return  wordsCount != 0;
}

std::vector<Word> GameStorage::GetWords()
{
	return m_db.get_all<Word>();
}

bool GameStorage::InsertUser(const std::string& username, const std::string& password)
{
	{

		try
		{

			PlayerDB user{ username, password };
			m_db.insert(user);
			return true;
		}
		catch (const std::exception& e)
		{
			std::cerr << "Database error: " << e.what() << std::endl;
			return false;
		}
	}
}

std::vector<PlayerDB> GameStorage::GetUsers()
{
	return m_db.get_all<PlayerDB>();
}

void GameStorage::PopulateStorage()
{
	std::ifstream inputFile("wordsIn.txt");
	std::string word;
	std::vector<Word>words;
	uint16_t difficulty;
	while (inputFile >> word >> difficulty)
	{
		Word w{ -1,word,difficulty };
		words.push_back(w);
	}
	m_db.insert_range(words.begin(), words.end());
}
