#pragma once

#include <QMainWindow>
#include "ui_Difficulty.h"
#include <QPushButton>
#include <Qlabel>
#include <QFontDatabase>

class Difficulty : public QMainWindow
{
	Q_OBJECT

public:
	Difficulty(QWidget *parent = nullptr);
	~Difficulty();

	void SetSendDifficulty(const uint16_t& d);
	uint16_t GetDifficultyFromWindow() const;
	void SendUsername(const std::string& u);
	std::string GetUsername() const;

private slots:
	void SelectDifficulty();

private:
	Ui::DifficultyClass ui;

	QPushButton* m_easy;
	QPushButton* m_medium;
	QPushButton* m_hard;

	uint16_t m_difficulty;
	std::string m_username;
};
