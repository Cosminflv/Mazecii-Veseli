#include "Lobby.h"
#include <QLabel>
#include "Difficulty.h"
#include "ClientExceptions.h"
#include "crow.h"
#include <cpr/cpr.h>

Lobby::Lobby(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setFont(QFont("8514oem", 20));
	setWindowTitle("Lobby");
	setFixedSize(400, 510);

	m_userDisplay = new QListWidget(this);
	m_userDisplay->setSpacing(3.6);
	m_userDisplay->setGeometry(80, 140, 230, 290);
	m_userDisplay->setFont(QFont("8514oem", 13));

	SetUi();
}

Lobby::~Lobby()
{}

void Lobby::InsertUser(const PlayerClient& client)
{
	m_users.push_back(client);
}

std::vector<PlayerClient> Lobby::GetClients() const
{
	return m_users;
}

QString Lobby::FromJsonToQString(const crow::json::detail::r_string value)
{
	std::string stringValue = std::string(value);
	return QString::fromUtf8(stringValue.c_str(), static_cast<int>(stringValue.size()));
}

void Lobby::SetUi()
{
	//m_users[0].SetAdminRole("NonAdmin");

	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/playerinfo" });

	if (response.error)
	{
		qDebug() << "Player Request failed with error: " << response.error.message;
		qDebug() << "HTTP status code: " << response.status_code;
		throw(PlayerRequestException("FAIL - Player Request"));
	}

	auto serverUsers = crow::json::load(response.text);

	for (const auto& user : serverUsers)
	{
		if (user.has("Username") && user.has("Status")) {
			if (user["Username"].t() == crow::json::type::String &&
				user["Status"].t() == crow::json::type::String) {

				PlayerClient client{ user["Username"].s(), user["AdminRole"].s() };
				qDebug() << "USERNAME: " <<  client.GetUsername() << " "
					<< "STATUS: " << client.GetAdminRole() << "\n";
				m_users.push_back(client);
			}
			else {
				// Handle incorrect data types
				std::cerr << "Invalid data types for Username or Status\n";
			}
		}
		else {
			// Handle missing keys
			std::cerr << "Missing keys Username or Status\n";
		}
	}

	for (const auto& u : m_users)
	{
		QListWidgetItem* newUser = new QListWidgetItem(QString::fromUtf8(u.GetUsername().c_str()));
		m_userDisplay->addItem(newUser);
	}

	m_userDisplay->setFont(QFont("8514oem", 13));
	m_userDisplay->show();

	if (m_users[0].GetAdminRole() == "NonAdmin")
	{
		QLabel* infotext = new QLabel("Waiting for game\nto start...", this);
		infotext->setGeometry(30, 30, 340, 100);
		infotext->setFont(QFont("", 30));
		infotext->setAlignment(Qt::AlignCenter);
		setStyleSheet("background-color:#e0ebe4");
		m_userDisplay->setStyleSheet("background-color:");
	}
	else
	{
		QLabel* infotext = new QLabel("Waiting for players\nto join...", this);
		infotext->setGeometry(30, 30, 340, 100);
		infotext->setFont(QFont("", 30));
		infotext->setAlignment(Qt::AlignCenter);
		m_startGame = new QPushButton("Start Game", this);
		m_startGame->setGeometry(125, 450, 150, 40);
		m_startGame->setFont(QFont("", 17));
		connect(m_startGame, &QPushButton::clicked, this, &Lobby::StartGame);
		setStyleSheet("background-color:#e0ebe4");
		m_userDisplay->setStyleSheet("background-color:");
		m_startGame->setStyleSheet("background-color:#ffe6cc; color:#5c8a74");
	}
}

void Lobby::StartGame()
{
	Difficulty* d = new Difficulty();
	d->SendUsername(m_users[0].GetUsername());

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