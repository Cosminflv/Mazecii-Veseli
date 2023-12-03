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
struct player2
{
	std::string username2;
	uint16_t score2;
};
inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Word",
			sql::make_column("id", &Word::id, sql::primary_key().autoincrement()),
			sql::make_column("description", &Word::description)
		),
		sql::make_table(
			"player2",
			sql::make_column("username2", &player2::username2, sql::primary_key().autoincrement()),
			sql::make_column("score2", &player2::score2)
		)
	);
}

