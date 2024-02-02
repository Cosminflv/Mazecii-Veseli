#pragma once

#include <QMainWindow>
#include "ui_PickAction.h"
#include "PlayerClient.h"
#include <QPushButton>
#include "Lobby.h"
#include "EnterCode.h"

class PickAction : public QMainWindow
{
	Q_OBJECT

public:
	PickAction(QWidget *parent = nullptr);
	~PickAction();

	void SetLoginUsername(const std::string& username);

private slots:
	void CreateRoom();
	void JoinRoom();

private:
	Ui::PickActionClass ui;
	std::string m_loginUsername;
	QPushButton* m_create;
	QPushButton* m_join;
};
