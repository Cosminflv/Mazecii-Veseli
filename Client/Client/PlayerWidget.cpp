#include "PlayerWidget.h"

#include <sstream>
#include <regex>
#include <string>

#include <cpr/cpr.h>
#include <crow.h>


PlayerWidget::PlayerWidget(QWidget* parent)
{
	setUpPlayerUI();
}

PlayerWidget::~PlayerWidget()
{
}

void PlayerWidget::setUpPlayerUI()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	m_playerList = new QTextEdit(this);
	
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/playerinfo" });

	auto players = crow::json::load(response.text);

	m_playerList->setReadOnly(true);
	layout->addWidget(m_playerList);
}
