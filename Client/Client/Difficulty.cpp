#include "Difficulty.h"
#include "Client.h"

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

void Difficulty::SetSendDifficulty(const uint16_t& d)
{
	m_difficulty = d;
}

uint16_t Difficulty::GetDifficultyFromWindow() const
{
	return m_difficulty;
}

void Difficulty::SendUsername(const std::string& u)
{
	m_username = u;
}

std::string Difficulty::GetUsername() const
{
	return m_username;
}

void Difficulty::SelectDifficulty()
{
	QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

	if (clickedButton == m_easy)
	{
		m_difficulty = 0;
	}
	else if (clickedButton == m_medium)
	{
		m_difficulty = 1;
	}
	else if (clickedButton == m_hard)
	{
		m_difficulty = 2;
	}

	qDebug() << m_difficulty;

	Client* w = new Client();
	w->SetDifficulty(m_difficulty);
	w->GetWordWidget()->UpdateWord(w->GetWordWidget()->FetchWordFromServer(m_difficulty));
	w->GetWordWidget()->GetWordLabel()->setFont(QFont("Rockwell", 20));
	qDebug() << "client difficulty set:" << w->GetDifficulty();
	w->GetChat()->SetClientUsername(m_username);
	QString qUsername = QString::fromUtf8(m_username.c_str());
	qDebug() << qUsername;
	w->GetPlayerWidget()->InsertPlayer(qUsername, 0);	
	w->show();
	w->GetPlayerWidget()->DisplayPlayers();
	hide();	
}
