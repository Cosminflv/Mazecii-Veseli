#include "Routing.h"
#include "Chat.h"
#include "PlayerDB.h"

void Routing::Run(GameStorage& storage)
{
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
	chat.WriteMessage({ "Server", "Hello darkness, my old friend!" });
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

	//405 Method Not Allowed
//CROW_ROUTE(m_app, "/receive_message")
//	.methods("POST"_method)
//	([&chat](const crow::request& req) {
//	// Access the transmitted JSON data from the client
//	auto json_data = crow::json::load(req.body);
//	if (!json_data) {
//		return crow::response(400);
//	}

//	if (json_data.has("username") && json_data.has("message")) {
//		std::string username = json_data["username"].s();
//		std::string password = json_data["message"].s();

//		chat.WriteMessage({ username, password });
//	}
//	else {
//		return crow::response(400);
//	}
//		});

	/*CROW_ROUTE(m_app, "/registerinfo")
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
	);*/
	m_app.port(18080).multithreaded().run();
}
