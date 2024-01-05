#pragma once

#include <QMainWindow>
#include "ui_Difficulty.h"
#include <QPushButton>
#include <Qlabel>
#include <QFontDatabase>
#include "PlayerClient.h"

class Difficulty : public QMainWindow
{
	Q_OBJECT

public:
	Difficulty(QWidget *parent = nullptr);
	~Difficulty();

	uint16_t GetDifficultyFromWindow() const;
	std::string GetLoginUsername() const;	
	std::vector<PlayerClient> GetClients() const;
	PlayerClient GetClient() const;

	void SetLoginUsername(const std::string& username);
	void SendAllClients(const std::vector<PlayerClient>& clients);
	void SetSendDifficulty(const uint16_t& d);
	void SetClient(const PlayerClient& client);
	
private slots:
	void SelectDifficulty();

private:
	Ui::DifficultyClass ui;

	QPushButton* m_easy;
	QPushButton* m_medium;
	QPushButton* m_hard;

	uint16_t m_difficulty;

	std::string m_loginUsername;
	PlayerClient m_you;
	std::vector<PlayerClient> m_clientsToPass;
};
