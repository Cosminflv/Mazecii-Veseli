#pragma once
#include <cpr/cpr.h>
#include <crow.h>
#include <sstream>
#include <regex>
#include <QtWidgets>
#include <vector>

class PlayerWidget: public QWidget
{
public:
	PlayerWidget(QWidget* parent = nullptr);
	~PlayerWidget();

private:
	void setUpPlayerUI();
	QString fromJsonToQString(const crow::json::detail::r_string value);

private:
	QListWidget* m_playerList;
};

