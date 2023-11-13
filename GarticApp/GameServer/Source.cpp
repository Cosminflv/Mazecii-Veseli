#include <filesystem>
#include <iostream>
#include <memory>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

int main() {
	crow::SimpleApp app;
	app.port(18080).multithreaded().run();

}