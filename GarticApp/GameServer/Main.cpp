#include <filesystem>
#include <memory>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Player.h"
#include "SubRound.h"
#include "GameData.h"
namespace sql = sqlite_orm;

int main()
{
	
	Storage db = createStorage("Data.sqlite"); 
	db.sync_schema(); 
	auto initWordsCount = db.count<Word>();
	if (initWordsCount == 0)
		populateStorage(db);
   auto wordsCount = db.count<Word>();
   std::cout << wordsCount << "\n";
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
	CROW_ROUTE(app, "/words")([&db]()
		{
			std::vector<crow::json::wvalue>wordsJson;
			for (const auto& word : db.iterate<Word>())
			{
				crow::json::wvalue w{
					{"id",word.id},
					{"description",word.description},

				};

				wordsJson.push_back(w);
			};
			return crow::json::wvalue{ wordsJson };
		}

	);

	CROW_ROUTE(app, "/word")([&subround]() {
	std::string randomWord = subround.SelectRandomWord();
		crow::json::wvalue wordJson;
		wordJson["word"] = randomWord;  
		return wordJson; 
		});
	app.port(18080).multithreaded().run();

}