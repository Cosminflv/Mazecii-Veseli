#pragma once
#include <string>
#include <vector>
#include <sqlite_orm/sqlite_orm.h>
#include <crow.h>
namespace sql = sqlite_orm;
#include "Player.h"
struct Word
{
	uint16_t id;
	std::string description;
	uint16_t difficulty;
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
		)
		/*sql::make_table(
			"Player_Score",
			sql::make_column("username", &Player::GetUsername(), sql::primary_key()),
			sql::make_column("score", &Player::getScore())
		)
		sql::make_table(
			"Player_Password",
			sql::make_column("username", &Player::GetUsername(), sql::primary_key()),
			sql::make_column("Password", &Player::getScore())
		)*/
	);
}

using Storage = decltype(createStorage(""));

void populateStorage(Storage& storage);