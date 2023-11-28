#pragma once
#include <QtWidgets>
#include <vector>

class PlayerWidget: public QWidget
{
public:
	PlayerWidget(QWidget* parent = nullptr);
	~PlayerWidget();

private:
	void setUpPlayerUI();

private:
	QListWidget* m_playerList;
};

