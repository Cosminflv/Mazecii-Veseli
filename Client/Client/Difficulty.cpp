#include "Difficulty.h"

Difficulty::Difficulty(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.setupUi(this);
	setFont(QFont("8514oem", 20));
	setWindowTitle("Select Game Difficulty");
	setFixedSize(420, 200);
	
	QLabel* choose = new QLabel("Choose difficulty level", this);
	choose->setFont(QFont("", 30));
	choose->setGeometry(28, 30, 370, 40);

	m_easy = new QPushButton("EASY", this);
	m_easy->setGeometry(40, 100, 90, 50);
	connect(m_easy, &QPushButton::clicked, this, &Difficulty::SelectDifficulty);

	m_medium = new QPushButton("MEDIUM", this);
	m_medium->setGeometry(160, 100, 90, 50);
	connect(m_medium, &QPushButton::clicked, this, &Difficulty::SelectDifficulty);

	m_hard = new QPushButton("HARD", this);
	m_hard->setGeometry(280, 100, 90, 50);
	connect(m_hard, &QPushButton::clicked, this, &Difficulty::SelectDifficulty);

	m_easy->setStyleSheet("background-color: #93d9a9;");
	m_medium->setStyleSheet("background-color: #d68854;");
	m_hard->setStyleSheet("background-color: #ab3036;");
}

Difficulty::~Difficulty()
{}

void Difficulty::SetSendDifficulty(const int& d)
{
	m_difficulty = d;
}

int Difficulty::GetDifficulty() const
{
	return m_difficulty;
}

bool Difficulty::DifficultyIsSet() const
{
	return m_isSet;
}

void Difficulty::SelectDifficulty()
{
	QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

	if (clickedButton == m_easy)
	{
		m_difficulty = 0;
		m_isSet = true;
	}
	else if (clickedButton == m_medium)
	{
		m_difficulty = 1;
		m_isSet = true;
	}
	else if (clickedButton == m_hard)
	{
		m_difficulty = 2;
		m_isSet = true;
	}
	qDebug() << m_difficulty;
}
