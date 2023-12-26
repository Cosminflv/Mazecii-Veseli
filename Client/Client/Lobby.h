#pragma once

#include <QMainWindow>
#include "ui_Lobby.h"
#include <QtWidgets>
#include <QPushButton>
#include <deque> // of logged in users; .front() will start game

class Lobby : public QMainWindow
{
	Q_OBJECT

public:
	Lobby(QWidget *parent = nullptr);
	~Lobby();

	void InsertUser(const QString& username);
	void DisplayUsers();
	std::deque<QString> GetPlayerQueue() const;

private slots:
	void StartGame();

private:
	Ui::LobbyClass ui;

	std::deque<QString> m_users;
	QPushButton* m_startGame;
	QListWidget* m_userDisplay;
};
