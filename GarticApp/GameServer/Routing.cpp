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

std::string m_hiddenWord = "";
std::string m_seenWord = "";

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

	CROW_ROUTE(m_app, "/gamestatus").methods("POST"_method)
		([&game](const crow::request& req)
		{
				crow::json::rvalue data = crow::json::load(req.body);
				if (!data)
				{
					return crow::response(400, "Invalid JSON format.\n");
				}
				std::string status = data["Gamestatus"].s();
				game.SetGameStatus(status);
				std::cout << "RECEIVED GAME STATUS: " << game.GetGameStatusAsString() << std::endl;
				return crow::response(200);
		});

	CROW_ROUTE(m_app, "/playerinfo")
		.methods("GET"_method)
		([&game]()
			{
				std::vector<crow::json::wvalue> playersJson;
				if (!game.GetPlayers().empty())
				{
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
	//500 Internal Server Error  
	CROW_ROUTE(m_app, "/users_score")([&storage]()
		{
			std::vector<crow::json::wvalue> usersJson;
			auto players = storage.GetPlayers();
			for (const auto& player : players)
			{
				crow::json::wvalue w{
					{"id", player.id},
					{"username", player.username},
					{"score", player.score}
				};

				usersJson.push_back(w);
			};
			return crow::json::wvalue{ usersJson };
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

	CROW_ROUTE(m_app, "/drawing")
		.methods("POST"_method)
		([](const crow::request& req) 
			{
				crow::json::rvalue jsonData = crow::json::load(req.body);
				if(!jsonData)
				{
					return crow::response(400, "Invalid JSON format");
				}

				if (!jsonData.has("Coordinates") || !jsonData.has("DrawingInfo"))
				{
					return crow::response(400, "Invalid JSON format");
				}
				
				const auto& coordinatesJSON = jsonData["Coordinates"];
				const auto& drawingInfoJSON = jsonData["DrawingInfo"];

				std::vector<std::pair<int, int>> coordinates;
				std::vector<std::pair<std::string, int>> drawingInfo;

				for (size_t i = 0; i < coordinates.size(); i++)
				{
					const auto& coord = coordinatesJSON[i];
					const auto& info = drawingInfoJSON[i];

					coordinates.emplace_back(coord[0].i(), coord[1].i());
					drawingInfo.emplace_back(info[0].s(), info[1].i());
				}
			
				return crow::response(200);
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
					//adaugata de mine~AndBuz
					storage.InsertPlayerScore(username);
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
				// cuvântul ascuns
				std::string hiddenWord = handler.HideTheWord(randomWord);

				// obiectul JSON care conține ambele variante ale cuvântului
				crow::json::wvalue wordJson;
				wordJson["visibleWord"] = randomWord;
				wordJson["hiddenWord"] = hiddenWord;
				m_hiddenWord = hiddenWord;
				m_seenWord = randomWord;
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

	T.SetUpdateWordCallback([&handler, this,&T]() {
			std::string updateWord = handler.UpdateWord(m_seenWord, m_hiddenWord);
			m_hiddenWord = updateWord;
			crow::response response;
			response.body = m_hiddenWord;
			return response;
		});

	T.StartTimer();
	CROW_ROUTE(m_app, "/updateWord/")
		.methods("GET"_method)
		([&handler, this]()
			{
				return m_hiddenWord;
			});

	CROW_ROUTE(m_app, "/logininfo")
		.methods("POST"_method)
		([&game, &handler, &storage](const crow::request& req)
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
					std::cout << "ADDED PLAYER: " << username << "\n";

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

Routing::Routing(GameStorage& storage, Game& game) : m_storage{ storage }
{
	m_routeHandler = RouteHandler(game);
}
