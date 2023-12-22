#include "PlayerWidget.h"
#include "ClientExceptions.h"
#include <crow/json.h>

PlayerWidget::PlayerWidget(QWidget* parent)
{
	setUpPlayerUI();
}

PlayerWidget::~PlayerWidget()
{
}

void PlayerWidget::setUpPlayerUI()
{
	m_playerList = new QListWidget(this);
	m_playerList->setSpacing(3.6);
	m_playerList->setFixedHeight(400);

	/*cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/playerinfo" });

	if (response.error) {
		throw(PlayerRequestException("Player Request has failed"));
	}

	auto playersFromServer = crow::json::load(response.text);

	for (const auto& playerFromServer : playersFromServer) {

		QString name = fromJsonToQString(playerFromServer["Username"].s());
		auto score = playerFromServer["Score"].u();
		m_players.push_back({ name, score });
	}*/

	/*for (const auto& player : m_players)
	{
		QString playerInfo = player.first + " - Score: " + QString::number(player.second);
		QListWidgetItem* user = new QListWidgetItem(playerInfo);
		user->setFont(QFont("8514oem", 13));
		m_playerList->addItem(user);
		m_playerList->show();
	}*/
}

QString PlayerWidget::fromJsonToQString(const crow::json::detail::r_string value)
{
	std::string stringValue = std::string(value);

	return QString::fromUtf8(stringValue.c_str(), static_cast<int>(stringValue.size()));
}

std::vector<std::pair<QString, u_int64>> PlayerWidget::GetPlayers() const
{
	return m_players;
}

void PlayerWidget::InsertPlayer(const QString& username, const u_int64& score)
{
	m_players.push_back({ username,score });
}

void PlayerWidget::DisplayPlayers()
{
	for (const auto& player : m_players)
	{
		QString playerInfo = player.first + " - Score: " + QString::number(player.second);
		QListWidgetItem* user = new QListWidgetItem(playerInfo);
		user->setFont(QFont("8514oem", 13));
		m_playerList->addItem(user);
		m_playerList->show();
	}
}
