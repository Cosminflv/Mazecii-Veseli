#pragma once
#include <string>
#include <vector>
#include <sqlite_orm/sqlite_orm.h>
#include <crow.h>
namespace sql = sqlite_orm;
#include "Player.h"
#include"PlayerDB.h"
struct Word
{
	uint16_t id;
	std::string description;
	uint16_t difficulty; // 0 pt cuvinte easy, 1 pt mediu, 2 pt hard
};
struct PlayerScore
{
	uint16_t id;
	std::string username;
	uint16_t score;
	uint16_t id_pp;

};
inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Word",
			sql::make_column("id", &Word::id, sql::primary_key().autoincrement()),
			sql::make_column("description", &Word::description),
			sql::make_column("difficulty",&Word::difficulty)
		),
	/*	sql::make_table(
			"Player_Score",
			sql::make_column("username", &Player::SetUsername, &Player::GetUsername, sql::primary_key()),
			sql::make_column("score", &Player::SetScore, &Player::GetScore)
		),*/
		sql::make_table(
			"Player_Score",
			sql::make_column("id", &PlayerScore::id, sql::primary_key()),
			sql::make_column("username", &PlayerScore::username),
			sql::make_column("score", &PlayerScore::score),
			sql::make_column("id_pp", &PlayerScore::id_pp, sql::foreign_key(&PlayerDB::SetId).references(&PlayerDB::GetId))
		),
		sql::make_table(
			"Player_Password",
			sql::make_column("id", &PlayerDB::SetId, &PlayerDB::GetId, sql::primary_key().autoincrement()),
			sql::make_column("username", &PlayerDB::SetUsername, &PlayerDB::GetUsername),
			sql::make_column("password", &PlayerDB::SetPassword ,&PlayerDB::GetPassword)
		)
	);
}

using Storage = decltype(createStorage(""));

class GameStorage
{
public:
	bool Initialize();
	std::vector<Word> GetWords();
	bool InsertUser(const std::string& username, const std::string& password);
	std::vector<PlayerDB>GetUsers();
	std::vector<PlayerScore>GetPlayers();
	bool CheckUser(const std::string& username, const std::string &password);

private:
	void PopulateStorage();

private:
	const std::string kDbFile{ "Database.sqlite" };

private:
	Storage m_db = createStorage(kDbFile);
};
