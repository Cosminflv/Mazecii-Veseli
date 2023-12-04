#pragma once
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;
#include "Player.h"
struct Word
{
	uint16_t id;
	std::string description;

};

inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Word",
			sql::make_column("id", &Word::id, sql::primary_key().autoincrement()),
			sql::make_column("description", &Word::description)
		)
		/*sql::make_table(
			"Player",
			sql::make_column("username", &Player::GetUsername(), sql::primary_key()),
			sql::make_column("score", &Player::getScore())
		)*/
	);
}
using Storage = decltype(createStorage(""));
void populateStorage(Storage& storage);