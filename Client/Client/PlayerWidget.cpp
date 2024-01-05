#include "PlayerWidget.h"
#include "ClientExceptions.h"
#include <crow/json.h>

PlayerWidget::PlayerWidget(QWidget* parent)
{
	setUpPlayerUI();
}

PlayerWidget::~PlayerWidget()
{
	// Empty
}

void PlayerWidget::setUpPlayerUI()
{
	m_playerList = new QListWidget(this);
	m_playerList->setSpacing(3.6);
	m_playerList->setFixedHeight(400);
}

QString PlayerWidget::fromJsonToQString(const crow::json::detail::r_string value)
{
	std::string stringValue = std::string(value);
	return QString::fromUtf8(stringValue.c_str(), static_cast<int>(stringValue.size()));
}

std::vector<PlayerClient> PlayerWidget::GetPlayers() const
{
	return m_players;
}

QListWidget* PlayerWidget::GetList() const
{
	return m_playerList;
}

void PlayerWidget::InsertPlayer(const PlayerClient& player)
{
	m_players.push_back(player);
}

void PlayerWidget::DisplayPlayers()
{
	for (const auto& player : m_players)
	{
		QString playerInfo = QString::fromUtf8(player.GetUsername().c_str()) + " - Score: " + QString::number(player.GetScore());
		QListWidgetItem* user = new QListWidgetItem(playerInfo);
		user->setFont(QFont("8514oem", 13));
		m_playerList->addItem(user);
	}
	m_playerList->show();
}

void PlayerWidget::UpdateList(const std::vector<PlayerClient>& clients)
{
	m_players = clients;
}
