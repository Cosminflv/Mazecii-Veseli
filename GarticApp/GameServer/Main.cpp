#include <filesystem>
#include <memory>

#include "Timer.h"
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Player.h"
#include "SubRound.h"
#include "GameData.h"
import Chat;
#include"PlayerDB.h"
#include "Routing.h"
#include <thread>


namespace sql = sqlite_orm;

int main()
{
	std::unique_ptr<Game> g = std::make_unique<Game>();
	GameStorage storage;
	Routing r(storage, std::move(g));
	r.Run();
}