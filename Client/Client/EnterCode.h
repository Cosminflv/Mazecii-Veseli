#pragma once

#include <QMainWindow>
#include "ui_EnterCode.h"
#include <QKeyEvent>
#include <QPushButton>
#include <QLineEdit>
#include <string>
#include <QLabel>

class EnterCode : public QMainWindow
{
	Q_OBJECT

public:
	EnterCode(QWidget *parent = nullptr);
	~EnterCode();
	std::string GetEnteredCode() const;
	void SetLoginUsername(const std::string& username);

private slots:
	void EnterGame();

protected:
	void keyPressEvent(QKeyEvent* e) override;

private:
	Ui::EnterCodeClass ui;
	QLineEdit* m_userText;
	std::string m_code;
	QPushButton* m_enterGame;
	std::string m_username;
};
