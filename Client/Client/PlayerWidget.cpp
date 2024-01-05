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
		QString playerInfo = QString::fromUtf8(player.GetUsername().c_str()) + "\n[" + QString::number(player.GetScore()) + " points]";
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

void PlayerWidget::UpdateScoreUI(const PlayerClient& client, const int16_t& newScore)
{
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i].GetUsername() == client.GetUsername())
		{
			m_players[i].UpdateScore(newScore);

			if (i < m_playerList->count())
			{
				QListWidgetItem* item = m_playerList->item(i);
				if (item)
				{
					QString playerInfo = QString::fromUtf8(m_players[i].GetUsername().c_str()) + "\n[" + QString::number(m_players[i].GetScore()) + " points]";
					item->setText(playerInfo);
				}
			}
			break; 
		}
	}
}
