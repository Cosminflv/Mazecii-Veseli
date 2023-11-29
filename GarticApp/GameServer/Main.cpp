#include <filesystem>
#include <memory>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Player.h"
#include "SubRound.h"

namespace sql = sqlite_orm;

int main()
{
	std::string username;
	std::string role;
	int16_t score;
		
	std::vector<Player*> players;
	for (std::ifstream input("PlayerData.txt"); !input.eof();)
	{
		input >> username >> role >> score;
		PlayerRole Role = ConvertToRole(role);
		Player* player = new Player(username, Role, score);
		players.push_back(player);
	}
	players[1]->SetPlayerStatus(true);
	std::cout << "PLAYER DATA:\n";
	for (int i = 0; i < players.size(); i++)
	{
		std::cout << "\nPLAYER " << i + 1 << "\n" << *players[i];
	}
	std::cout << "\n----------------------------------------------------------------\n";
	
	SubRound subround;

	crow::SimpleApp app;

	CROW_ROUTE(app, "/playerinfo")([&players]()
		{
			std::vector<crow::json::wvalue> playersJson;
			for (const auto& player : players)
			{
				crow::json::wvalue p
				{
					{"Username", player->GetUsername()}, {"Role", player->GetRoleAsString()},
					{"Score", player->GetScore()}, {"Status", player->GetPlayerStatus()}
				};

				playersJson.push_back(p);
			}
			return crow::json::wvalue{ playersJson };
		});
	
}