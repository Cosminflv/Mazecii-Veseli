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
namespace sql = sqlite_orm;

int main()
{
	Timer T{ 1 };
	Storage db = createStorage("Datab.sqlite");
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
	Chat chat;

	chat.WriteMessage({ "Server", "Hello world!" });

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
					{"difficulty",word.difficulty}

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

CROW_ROUTE(app, "/words/<int>")
	.methods("GET"_method)
	([&db](const crow::request& req, int difficulty)
		{
			std::vector<crow::json::wvalue> wordsJson;
			auto allWords = db.iterate<Word>();

			for (const auto& word : allWords)
			{
				if (word.difficulty == static_cast<uint16_t>(difficulty))
				{
					crow::json::wvalue w{
						{"id", word.id},
						{"description", word.description},
						{"difficulty", word.difficulty}
					};

					wordsJson.push_back(w);
				}
			}

			return crow::json::wvalue{ wordsJson };
		});
	CROW_ROUTE(app, "/chat")([&chat]()
		{
			std::vector<crow::json::wvalue> chatMessagesJson;
			auto chatMessages = chat.getChat();
			for (const auto& message : chatMessages)
			{
				crow::json::wvalue m
				{
					{"Username", message.first},
					{"Message", message.second},
				};

				chatMessagesJson.push_back(m);
			}
			return crow::json::wvalue{ chatMessagesJson };
		});

	CROW_ROUTE(app, "/receive_message")
		.methods("POST"_method)
		([&chat](const crow::request& req) {
		// Access the transmitted JSON data from the client
		auto json_data = crow::json::load(req.body);
		if (!json_data) {
			return crow::response(400);
		}

		if (json_data.has("username") && json_data.has("message")) {
			std::string username = json_data["username"].s();
			std::string password = json_data["message"].s();

			chat.WriteMessage({ username, password });
		}
		else {
			return crow::response(400);
		}
			});
	

	app.port(18080).multithreaded().run();
}