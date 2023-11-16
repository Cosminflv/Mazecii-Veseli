#include "GarticApp.h"
#include <QtWidgets/QApplication>
//#include "Player.h"
//#include "SubRound.h"
//#include <fstream>
//#include <vector>
//#include"Game.h"

//import player;
//import playerRole;
//
//int main(int argc, char* argv[])
//{
//	QApplication a(argc, argv);
//	GarticApp w;
//	std::ofstream output("Output.txt");
//	std::string username;
//	std::string role;
//	int16_t score;
	//Game game;

	//for (std::ifstream input ("Input.txt"); !input.eof(); )
	//{
	//	input >> username >> role >> score;
	//	PlayerRole Role = ConvertToRole(role);
	//	Player* player = new Player(username, Role, score);
	//	if (game.CheckUniquePlayerUsername(player) == true)
	//	{
	//		game.AddPlayer(player);
	//	}
	//	else
	//	{
	//		output << "Username taken! Enter another: " << username;
	//	}
	//}
	//
	//std::vector<Player*>playersInGame = game.GetPlayers();
	//Player* player = playersInGame[0];
	//SubRound runda(playersInGame, "ana");
	//for (auto player : playersInGame)
	//{
	//	output << player->GetPlayerStatus() << std::endl;
	//	output << *player << "\n";
	//}

	/*using namespace garticApp;
	std::vector<mPlayer*> players;
	for (std::ifstream input("Input.txt"); !input.eof();)
	{
		input >> username >> role >> score;
		mPlayerRole Role = mConvertToRole(role);
		mPlayer* player = new mPlayer(username, Role, score);
		players.push_back(player);
	}
	players[1]->SetPlayerStatus(true);
	for (auto player : players)
	{
		output << *player;
	}

	w.show();*/
	/*return a.exec();
}*/

