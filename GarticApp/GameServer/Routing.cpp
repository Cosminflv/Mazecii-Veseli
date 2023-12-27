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


void Routing::Run(Game& game)
{
	GameStorage storage = m_storage;
	RouteHandler handler = m_routeHandler;

	CROW_ROUTE(m_app, "/gamestatus")([&game]()
		{
			std::vector<crow::json::wvalue> playersJson;

			crow::json::wvalue p
			{
				{"Gamestatus", game.GetGameStatusAsString()}
			};
			return crow::json::wvalue{ p };
		});

	CROW_ROUTE(m_app, "/playerinfo")([&game]()
		{
			std::vector<crow::json::wvalue> playersJson;
			for (const auto& player : game.GetPlayers())
			{
				crow::json::wvalue p
				{
					{"Username", player->GetUsername()}, {"PlayerRole", player->GetPlayerRoleAsString()},
					{"Score", player->GetScore()}, {"Status", player->GetPlayerStatus()},
					{"AdminRole", player->GetAdminRoleAsString()}
				};

				playersJson.push_back(p);
			}
			return crow::json::wvalue{ playersJson };
		});

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

	CROW_ROUTE(m_app, "/chat")([&game]()
		{
			std::vector<crow::json::wvalue> chatMessagesJson;
			auto chatMessages = game.GetChat().getChatVector();
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
		([&game, &handler](const crow::request& req)
			{

				crow::json::rvalue json_data = crow::json::load(req.body);
				if (!json_data) {
					return crow::response(400, "Invalid JSON format");
				}

				if (!json_data.has("username") || !json_data.has("message"))
					return crow::response(400, "Invalid JSON format");

				std::string username = json_data["username"].s();
				std::string message = json_data["message"].s();
				handler.WriteMessage(username, message);
				std::cout << "Received message from " << username << ": " << message;

				if (handler.CheckEnteredMessage(message)) {
					//wonScore = subround.calculateScore(
					//totalScore = m_game.GetLeaderBoard()[username] + wonScore
					//update leaderboard m_game.UpdateLeaderBoard(username, totalScore)
					//toate wrappuite intr-o metoda din handler
				}

				return crow::response(200);
			});


	CROW_ROUTE(m_app, "/registerinfo")
		.methods("POST"_method)
		([&handler, &storage](const crow::request& req)
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

				if (storage.InsertUser(username, password))
				{
					return crow::response(200);
					handler.AddPlayer(username);
				}
				else
				{
					return crow::response(100, "Username already exists");
				}
			}
	);

	CROW_ROUTE(m_app, "/word/<int>")
		.methods("GET"_method)
		([&handler](int difficulty)
			{
				std::string randomWord = handler.PickWord(static_cast<uint16_t>(difficulty));

				// Creează cuvântul ascuns
				std::string hiddenWord = handler.HideTheWord(randomWord);

				// Construiește obiectul JSON care conține ambele variante ale cuvântului
				crow::json::wvalue wordJson;
				wordJson["visibleWord"] = randomWord;
				wordJson["hiddenWord"] = hiddenWord;

				return wordJson;
			});

	Timer T{ 3 };
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
		([&handler, &storage](const crow::request& req)
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

				if (storage.CheckUser(username, password) == true)
				{
					std::cout << "Received username: " << username << std::endl;
					std::cout << "Received password: " << password << std::endl;
					//db.replace(user);
					handler.AddPlayer(username);
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

Routing::Routing(GameStorage& storage) : m_storage{ storage }
{
}
