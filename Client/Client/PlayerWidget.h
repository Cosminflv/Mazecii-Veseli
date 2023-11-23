#pragma once
#include <QtWidgets>

class PlayerWidget: public QWidget
{
public:
	PlayerWidget(QWidget* parent = nullptr);
	~PlayerWidget();

private:
	void setUpPlayerUI();

private:
	QTextEdit* m_playerList;
};

