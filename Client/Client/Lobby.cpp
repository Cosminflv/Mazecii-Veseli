#include "Lobby.h"
#include <QLabel>
#include "Difficulty.h"
#include "crow.h"
#include <cpr/cpr.h>

Lobby::Lobby(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setFont(QFont("8514oem", 20));
	setWindowTitle("Lobby");
	setFixedSize(400, 510);

	QLabel* infotext = new QLabel("Waiting for players\nto join...", this);
	infotext->setGeometry(30, 30, 340, 100);
	infotext->setFont(QFont("", 30));
	infotext->setAlignment(Qt::AlignCenter);

	m_userDisplay = new QListWidget(this);
	m_userDisplay->setSpacing(3.6);
	m_userDisplay->setGeometry(80, 140, 230, 290);

	m_startGame = new QPushButton("Start Game", this);
	m_startGame->setGeometry(125, 450, 150, 40);
	m_startGame->setFont(QFont("", 17));
	connect(m_startGame, &QPushButton::clicked, this, &Lobby::StartGame);

	// if player is not admin -> "waiting for game to start.."
	// -> can see the player list
	// -> can't see start game button

	setStyleSheet("background-color:#e0ebe4");
	m_userDisplay->setStyleSheet("background-color:");
	m_startGame->setStyleSheet("background-color:#ffe6cc; color:#5c8a74");
}

Lobby::~Lobby()
{}

void Lobby::InsertUser(const QString& username)
{
	m_users.push_back(username);
}

void Lobby::DisplayUsers()
{
	m_userDisplay->setFont(QFont("8514oem", 13));
	for (const auto& u : m_users)
	{
		QListWidgetItem* newUser = new QListWidgetItem(u);
		m_userDisplay->addItem(newUser);
	}
	m_userDisplay->show();
}

std::deque<QString> Lobby::GetPlayerQueue() const
{
	return m_users;
}

void Lobby::StartGame()
{
	//difficulty window will show only for admin
	//rest of the players will go into the game

	Difficulty* d = new Difficulty();
	d->SendUsername(m_users.front().toUtf8().constData());

	crow::json::wvalue json;
	json["Gamestatus"] = "Playing";
	std::string jsString = json.dump();
	cpr::Response statusResponse = cpr::Post(cpr::Url("http://localhost:18080/gamestatus"), cpr::Body{ jsString });
	if (statusResponse.status_code == 200)
	{
		d->show();
		hide();
	}
}