#include "PlayerWidget.h"

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
	m_playerList->setReadOnly(true);
	layout->addWidget(m_playerList);
}
