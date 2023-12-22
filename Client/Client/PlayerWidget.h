#pragma once
#include <cpr/cpr.h>
#include <crow.h>
#include <sstream>
#include <regex>
#include <QtWidgets>
#include <vector>

class PlayerWidget: public QWidget
{
public:
	PlayerWidget(QWidget* parent = nullptr);
	~PlayerWidget();
	std::vector<std::pair<QString, u_int64>> GetPlayers() const;
	void InsertPlayer(const QString& username, const u_int64& score);
	void DisplayPlayers();

private:
	void setUpPlayerUI();
	QString fromJsonToQString(const crow::json::detail::r_string value);

private:
	QListWidget* m_playerList;
	std::vector<std::pair<QString, u_int64>> m_players;
};

