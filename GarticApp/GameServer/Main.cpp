#include <filesystem>
#include <memory>

#include "Timer.h"
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Player.h"
#include "SubRound.h"
#include "GameData.h"
#include "Chat.h"
#include"PlayerDB.h"
#include "Routing.h"
#include <thread>


namespace sql = sqlite_orm;

int main()
{
	
	GameStorage storage;
	Routing r(storage);
	r.Run();
}