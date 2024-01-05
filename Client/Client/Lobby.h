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

	std::string GetLoginUsername() const;
	void SetLoginUsername(const std::string& username);
	std::vector<PlayerClient> GetClients() const;
	QString FromJsonToQString(const crow::json::detail::r_string value);	
	void SetUi();

private slots:
	void StartGame();

private:
	Ui::LobbyClass ui;

	std::string m_loginUsername;
	PlayerClient m_you;
	std::vector<PlayerClient> m_users;
	QPushButton* m_startGame;
	QListWidget* m_userDisplay;
};
