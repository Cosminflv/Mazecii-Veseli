#include "GarticApp.h"
#include <QtWidgets/QApplication>
#include "Player.h"

#include "SubRound.h"
#include <fstream>
#include <vector>
#include"Game.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	GarticApp w;
	std::ofstream output("Output.txt");
	std::string username;
	std::string role;
	int16_t score;
	Game game;

	for (std::ifstream input ("Input.txt"); !input.eof(); )
	{
		input >> username >> role >> score;
		PlayerRole Role = ConvertToRole(role);
		Player* player = new Player(username, Role, score);
		game.AddPlayer(player);
	}
	
	std::vector<Player*>playersInGame = game.GetPlayers();
	//Player* player = playersInGame[0];
	SubRound runda(playersInGame, "ana");
	for (auto player : playersInGame)
	{
		output << player->GetPlayerStatus() << std::endl;
		output << *player << "\n";
	}
	
	w.show();
	return a.exec();
}

