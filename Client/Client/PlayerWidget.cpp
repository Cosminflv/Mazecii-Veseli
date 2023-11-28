#include "PlayerWidget.h"

//#include <sstream>
//#include <regex>
//#include <string>
//
//#include <cpr/cpr.h>
//#include <crow.h>


PlayerWidget::PlayerWidget(QWidget* parent)
{
	setUpPlayerUI();
}

PlayerWidget::~PlayerWidget()
{
}

void PlayerWidget::setUpPlayerUI()
{
	QFile file("D:\\_IOANA\\Documents\\0_AN_II_SEM_I\\MC\\GarticApp\\Client\\Client\\Players.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Error opening file: " << file.errorString();
		return;
	}
	QTextStream in(&file);
	int playercount;
	in >> playercount;
	std::vector<std::pair<QString, float>>players;

	while (playercount != 0)
	{
		QString name; float score;
		in >> name >> score;
		players.push_back({ name, score });
		playercount--;
	}

	m_playerList = new QListWidget(this);
	m_playerList->setSpacing(3.6);
	m_playerList->setFixedHeight(400);

	for (const auto& player : players)
	{
		QString playerInfo = player.first + " - Score: " + QString::number(player.second);
		QListWidgetItem* user = new QListWidgetItem(playerInfo);
		user->setFont(QFont("Arial", 13));
		m_playerList->addItem(user);
	}
	
	file.close();

	/*cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/playerinfo" });

	auto players = crow::json::load(response.text);*/
}
