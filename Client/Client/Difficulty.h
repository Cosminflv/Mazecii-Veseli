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
	void SetSendDifficulty(const int& d);
	int GetDifficulty() const;
	bool DifficultyIsSet() const;

private slots:
	void SelectDifficulty();

private:
	Ui::DifficultyClass ui;

	QPushButton* m_easy;
	QPushButton* m_medium;
	QPushButton* m_hard;

	int m_difficulty;
	bool m_isSet;
};
