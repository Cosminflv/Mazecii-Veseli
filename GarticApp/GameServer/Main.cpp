#include <filesystem>
#include <memory>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

import PlayerRole;

int main()
{
	using namespace garticApp;
	std::string role;
	std::cin >> role;
	PlayerRole Role = ConvertToRole(role);
	std::cout << "Player's role is: " << Role << "\n";

	crow::SimpleApp app;
	app.port(18080).multithreaded().run();

}