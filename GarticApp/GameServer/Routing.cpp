#include "Routing.h"
#include "Chat.h"
#include "PlayerDB.h"
#include "SubRound.h"
#include "Chat.h"
#include "Timer.h"
#include <filesystem>
#include <memory>

#include "Timer.h"
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Player.h"
#include "GameData.h"
#include"PlayerDB.h"
#include <thread>


void Routing::Run(GameStorage& storage)
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

	CROW_ROUTE(m_app, "/playerinfo")([&players]()
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

	CROW_ROUTE(m_app, "/")([]() {
		return "Meow";
		});

	CROW_ROUTE(m_app, "/words")([&storage]()
		{

			std::vector<crow::json::wvalue>wordsJson;
			auto words = storage.GetWords();
			for (const auto& word : words)
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
	CROW_ROUTE(m_app, "/users")([&storage]()
		{

			std::vector<crow::json::wvalue>usersJson;
			auto users = storage.GetUsers();
			for (const auto& user : users)
			{
				crow::json::wvalue w{
					{"id",user.GetId()},
					{"username",user.GetUsername()},
					{"password",user.GetPassword()}

				};

				usersJson.push_back(w);
			};
			return crow::json::wvalue{ usersJson };
		}
	);

	CROW_ROUTE(m_app, "/words/<int>")
		.methods("GET"_method)
		([&storage](const crow::request& req, int difficulty)
			{
				std::vector<crow::json::wvalue> wordsJson;
				auto allWords = storage.GetWords();

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


	Chat chat;
	CROW_ROUTE(m_app, "/chat")([&chat]()
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

	CROW_ROUTE(m_app, "/receive_message")
		.methods("POST"_method)
		([&chat](const crow::request& req)
			{

				crow::json::rvalue json_data = crow::json::load(req.body);
				if (!json_data) {
					return crow::response(400, "Invalid JSON format");
				}

				if (json_data.has("username") && json_data.has("message")) {
					std::string username = json_data["username"].s();
					std::string message = json_data["message"].s();
					chat.WriteMessage({ username, message });
					std::cout << "Received message from " << username << ": " << message;
					return crow::response(200);
				}
			});


	CROW_ROUTE(m_app, "/registerinfo")
		.methods("POST"_method)
		([&](const crow::request& req)
			{
				crow::json::rvalue jsonData = crow::json::load(req.body);
				if (!jsonData)
				{
					return crow::response(400, "Invalid JSON format");
				}
				std::string username = jsonData["username"].s();
				std::string password = jsonData["password"].s();
				PlayerDB user;
				user.SetUsername(username);
				user.SetPassword(password);
				std::cout << "Received username: " << username << std::endl;
				std::cout << "Received password: " << password << std::endl;

				GameStorage gameStorage;
				if (gameStorage.InsertUser(username, password))
				{
					return crow::response(200);
				}
				else
				{
					return crow::response(100, "Username already exists");
				}
			}
	);

	SubRound subround;
	CROW_ROUTE(m_app, "/word/<int>")
		.methods("GET"_method)
		([&subround](int difficulty)
			{
				std::string randomWord = subround.SelectRandomWord(static_cast<uint16_t>(difficulty));
				crow::json::wvalue wordJson;
				wordJson["word"] = randomWord;
				return wordJson;
			});

	
	//idk
		//CROW_ROUTE(m_app, "/registerinfo")
		//	.methods("POST"_method)
		//	([](const crow::request& req)
		//		{
		//			crow::json::rvalue jsonData = crow::json::load(req.body);
		//			if (!jsonData)
		//			{
		//				return crow::response(400, "Invalid JSON format");
		//			}
		//			std::string username = jsonData["username"].s();
		//			std::string password = jsonData["password"].s();
		//			PlayerDB user;
		//			user.SetUsername(username);
		//			user.SetPassword(password);
		//			std::cout << "Received username: " << username << std::endl;
		//			std::cout << "Received password: " << password << std::endl;
		//			//db.replace(user);
		//			return crow::response(200);
		//		}
		//);


	Timer T{ 1 };
	CROW_ROUTE(m_app, "/timer")([&T]()
			{
				std::chrono::milliseconds milliseconds = T.GetRemainingTime();
				int seconds = static_cast<int>(milliseconds.count()) / 1000;

					crow::json::wvalue secondsJson
					{
						{"Seconds", seconds},
					};

					return  secondsJson;
			});

	T.StartTimer();



	CROW_ROUTE(m_app, "/logininfo")
		.methods("POST"_method)
		([](const crow::request& req)
			{
				crow::json::rvalue jsonData = crow::json::load(req.body);
				if (!jsonData)
				{
					return crow::response(400, "Invalid JSON format");
				}
				std::string username = jsonData["username"].s();
				std::string password = jsonData["password"].s();
				PlayerDB user;
				user.SetUsername(username);
				user.SetPassword(password);
				GameStorage gameStorage;
				if (gameStorage.CheckUser(username, password) == true)
				{
					std::cout << "Received username: " << username << std::endl;
					std::cout << "Received password: " << password << std::endl;
					//db.replace(user);
					return crow::response(200);
				}
				else
				{
					return crow::response(101, "User doesn't exist");
				}
			}
	);


	m_app.port(18080).multithreaded().run();
}
