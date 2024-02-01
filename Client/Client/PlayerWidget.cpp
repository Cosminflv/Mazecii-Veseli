#include "PlayerWidget.h"
#include "ClientExceptions.h"
#include <crow/json.h>

PlayerWidget::PlayerWidget(QWidget* parent)
{
	m_playerList = new QListWidget(this);
	m_playerList->setSpacing(3.6);
	m_playerList->setFixedHeight(400);
	setFont(QFont("8514oem", 13));
	setStyleSheet("background-color: #ffffff");
}

PlayerWidget::~PlayerWidget()
{
	// Empty
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
	m_playerList->clear();

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

void PlayerWidget::UpdateScoreUI(const PlayerClient& client)
{
	int16_t newScore = 0;
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/playerinfo" });
	if (response.status_code == 200)
	{
		crow::json::rvalue json_data = crow::json::load(response.text);
		if (json_data)
		{
			for (const auto& playerJson : json_data)
			{
				if (playerJson["Username"].s() == client.GetUsername())
				{
					newScore = playerJson["Score"].i();
				}
			}
		}

		auto it = std::find_if(m_players.begin(), m_players.end(),
			[&](const auto& player) {return player.GetUsername() == client.GetUsername(); });

		if (it != m_players.end())
		{
			it->UpdateScore(newScore);
			auto index = std::distance(m_players.begin(), it); // calculated distance from begin() to iterator to get pos
			if (index < m_playerList->count())
			{
				QListWidgetItem* item = m_playerList->item(index);
				if (item)
				{
					QString playerInfo = QString::fromUtf8(it->GetUsername().c_str()) + 
						"\n[" + QString::number(it->GetScore()) + " points]";
					item->setText(playerInfo);
				}
			}
		}
	}
}

void PlayerWidget::SetUi()
{
	m_requestsTimer = new QTimer(this);
	m_requestsTimer->setInterval(1000);
	m_requestsTimer->start();
	connect(m_requestsTimer, &QTimer::timeout, this, &PlayerWidget::fetchAndUpdatePlayers);
}

void PlayerWidget::fetchAndUpdatePlayers()
{
	std::thread([this]() {
		try {
			m_players.clear();
			cpr::Response responsePlayer = cpr::Get(cpr::Url{ "http://localhost:18080/playerinfo" });

			if (responsePlayer.error)
			{
				qDebug() << "Player Request failed with error: " << responsePlayer.error.message;
				qDebug() << "HTTP status code: " << responsePlayer.status_code;
				throw(PlayerRequestException("FAIL - Player Request"));
			}

			auto serverUsers = crow::json::load(responsePlayer.text);

			for (const auto& user : serverUsers)
			{
				if (user.has("Username") && user.has("Status")) {
					if (user["Username"].t() == crow::json::type::String &&
						user["Status"].t() == crow::json::type::String)
					{
						int16_t score = static_cast<int16_t>(user["Score"].i());
						PlayerClient client{ user["Username"].s(), user["Status"].s(), score, user["PlayerRole"].s(), user["AdminRole"].s() };
						m_players.push_back(client);
					}
					else {
						std::cerr << "Invalid data types for Username or Status\n";
					}
				}
				else {
					std::cerr << "Missing keys Username or Status\n";
				}
			}

			QMetaObject::invokeMethod(this, [this]() {
				DisplayPlayers();
				}, Qt::QueuedConnection);

		}
		catch (const LobbyRequestException& e) {
			qDebug() << "Lobby request exception: " << e.what();
		}
		}).detach();
}
