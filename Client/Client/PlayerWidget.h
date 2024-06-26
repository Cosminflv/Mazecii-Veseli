#pragma once
#include <cpr/cpr.h>
#include <crow.h>
#include <sstream>
#include <regex>
#include <QtWidgets>
#include <vector>
#include "PlayerClient.h"

class PlayerWidget: public QWidget
{
public:
	PlayerWidget(QWidget* parent = nullptr);
	~PlayerWidget();
	std::vector<PlayerClient> GetPlayers() const;
	QListWidget* GetList() const;
	void InsertPlayer(const PlayerClient& player);
	void DisplayPlayers();
	void UpdateList(const std::vector<PlayerClient>& clients);
	void UpdateScoreUI(const PlayerClient& client);
	void SetUi();

private:
	QString fromJsonToQString(const crow::json::detail::r_string value);

private slots:
	void fetchAndUpdatePlayers();
	//void UpdateUi();

private:
	QListWidget* m_playerList;
	QTimer* m_requestsTimer;

	std::vector<PlayerClient> m_players;
};

