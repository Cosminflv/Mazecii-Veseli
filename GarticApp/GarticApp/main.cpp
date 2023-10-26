#include "GarticApp.h"
#include <QtWidgets/QApplication>
#include "Player.h"
#include "GuesserPlayer.h"
#include "PainterPlayer.h"
#include <fstream>
#include <vector>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	GarticApp w;
	std::ofstream output("Output.txt");
	std::string username;
	std::string role;
	int16_t score;

	std::vector<Player*> players;

	for (std::ifstream input ("Input.txt"); !input.eof(); )
	{
		input >> username >> role >> score;
		if (role == "Guesser")
		{
			PlayerRole Role = ConvertToRole(role);
			Player* player = new GuesserPlayer(username, Role, score);
			players.push_back(player);
		}
		else if (role == "Painter")
		{
			PlayerRole Role = ConvertToRole(role);
			Player* player = new PainterPlayer(username, Role, score);
			players.push_back(player);
		}
	}

	for (auto player : players)
	{
		output << *player << "\n";
	}

	w.show();
	return a.exec();
}

