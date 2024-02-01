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

private:
	std::string GenerateGameCode();
	void AdminSetUp();
	void NonAdminSetUp();
	std::vector<PlayerClient> PlayerSetUp();

private slots:
	void StartGame();
	void fetchAndUpdateLobby();
	void fetchAndUpdateGameState();
	void UpdateGameState(bool updateGameStateCalled);
	void UpdateUi(std::vector<PlayerClient> m_players);
	void SendCode();
	void ShowErrorMessage();
	void HideErrorMessage();

private:
	Ui::LobbyClass ui;
	QTimer* m_requestsTimer;
	std::atomic<bool> stopThreadFlag;
	bool updateGameStateCalled;

	std::string m_code;
	std::string m_loginUsername;
	PlayerClient m_you;
	std::vector<PlayerClient> m_users;
	QPushButton* m_startGame;
	QListWidget* m_userDisplay;
	QPushButton* m_generateCode;
	QLabel* error;
	QTimer timedError;
};
