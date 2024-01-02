#pragma once

#include <QMainWindow>
#include "crow.h"
#include <cpr/cpr.h>
#include "ui_Lobby.h"
#include <QtWidgets>
#include <QPushButton>
#include <vector>
#include "PlayerClient.h"

class Lobby : public QMainWindow
{
	Q_OBJECT

public:
	Lobby(QWidget *parent = nullptr);
	~Lobby();

	void InsertUser(const PlayerClient& client);	
	std::vector<PlayerClient> GetClients() const;
	void SetUi();
	QString FromJsonToQString(const crow::json::detail::r_string value);	

private slots:
	void StartGame();
	void DisplayUsers();

private:
	Ui::LobbyClass ui;

	std::vector<PlayerClient> m_users;
	QPushButton* m_startGame;
	QListWidget* m_userDisplay;
};
