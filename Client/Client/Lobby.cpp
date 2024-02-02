#include "Lobby.h"
#include <QLabel>
#include "Difficulty.h"
#include "Client.h"
#include "ClientExceptions.h"
#include "crow.h"
#include <cpr/cpr.h>
 
Lobby::Lobby(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	stopThreadFlag = false;

	setFont(QFont("8514oem", 20));
	setWindowTitle("Lobby");
	setFixedSize(400, 510);
	m_userDisplay = new QListWidget(this);
	m_userDisplay->setSpacing(3.6);
	m_userDisplay->setFont(QFont("8514oem", 13));

	error = new QLabel("Game can't start with one player!", this);
	error->setGeometry(35, 410, 330, 20);
	error->setFont(QFont("8514oem", 13));
	error->setStyleSheet("background-color: #cd4c52 ;color: #f2f2f2;");
	error->hide();
	connect(&timedError, &QTimer::timeout, this, &Lobby::HideErrorMessage);
	timedError.setInterval(5000);
}

Lobby::~Lobby()
{}

std::string Lobby::GetLoginUsername() const
{
	return m_loginUsername;
}

void Lobby::SetLoginUsername(const std::string& username)
{
	this->m_loginUsername = username;
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

PlayerClient Lobby::GetClient() const
{
	return m_you;
}

void Lobby::SetClientARole(const std::string& role)
{
	m_you.SetAdminRole(role);
}

void Lobby::AdminSetUp()
{
	QLabel* infotext = new QLabel("Waiting for players\nto join...", this);
	infotext->setGeometry(30, 30, 340, 100);
	infotext->setFont(QFont("", 30));
	infotext->setAlignment(Qt::AlignCenter);
	m_generateCode = new QPushButton("generate game code", this);
	m_generateCode->setGeometry(100, 150, 200, 30);
	m_generateCode->setFont(QFont("", 15));
	connect(m_generateCode, &QPushButton::clicked, this, &Lobby::SendCode);
	m_startGame = new QPushButton("Start Game", this);
	m_startGame->setGeometry(125, 450, 150, 40);
	m_startGame->setFont(QFont("", 17));
	connect(m_startGame, &QPushButton::clicked, this, &Lobby::StartGame);
	m_userDisplay->setGeometry(80, 195, 230, 240);
	m_generateCode->setStyleSheet("background-color:#c1d7c9; color:#660000");
	m_userDisplay->setStyleSheet("background-color: #faf3ea");
	m_startGame->setStyleSheet("background-color:#ffe6cc; color:#5c8a74");
	setStyleSheet("background-color:#e0ebe4");
}

void Lobby::NonAdminSetUp()
{
	QLabel* infotext = new QLabel("Waiting for game\nto start...", this);
	infotext->setGeometry(30, 30, 340, 100);
	infotext->setFont(QFont("", 30));
	infotext->setAlignment(Qt::AlignCenter);
	m_userDisplay->setGeometry(80, 140, 230, 290);
	m_userDisplay->setStyleSheet("background-color: #faf3ea");
	setStyleSheet("background-color:#e0ebe4");
}

std::vector<PlayerClient> Lobby::PlayerSetUp()
{
	cpr::Response responsePlayer = cpr::Get(cpr::Url{ "http://localhost:18080/playerinfo" });

	if (responsePlayer.error)
	{
		qDebug() << "Player Request failed with error: " << responsePlayer.error.message;
		qDebug() << "HTTP status code: " << responsePlayer.status_code;
		throw(PlayerRequestException("FAIL - Player Request"));
	}

	auto serverUsers = crow::json::load(responsePlayer.text);

	std::vector<PlayerClient> players;

	for (const auto& user : serverUsers)
	{
		if (user.has("Username") && user.has("Status")) {
			if (user["Username"].t() == crow::json::type::String &&
				user["Status"].t() == crow::json::type::String)
			{
				int16_t score = static_cast<int16_t>(user["Score"].i());
				PlayerClient client{ user["Username"].s(), user["Status"].s(), score, user["PlayerRole"].s(), user["AdminRole"].s() };
				players.push_back(client);

				if (m_loginUsername == user["Username"].s())
				{
					m_you.SetUsername(user["Username"].s());
					m_you.UpdateStatus(user["Status"].s());
					m_you.UpdateScore(score);
					m_you.UpdatePlayerRole(user["PlayerRole"].s());
				}
			}
			else {
				std::cerr << "Invalid data types for Username or Status\n";
			}
		}
		else {
			std::cerr << "Missing keys Username or Status\n";
		}
	}
	return players;
}

void Lobby::SetUi()
{
	m_requestsTimer = new QTimer(this);
	m_requestsTimer->setInterval(1000);
	m_requestsTimer->start();
	connect(m_requestsTimer, &QTimer::timeout, this, &Lobby::fetchAndUpdateLobby);
	connect(m_requestsTimer, &QTimer::timeout, this, &Lobby::fetchAndUpdateGameState);

	m_users = std::move(PlayerSetUp());

	for (const auto& u : m_users)
	{
		QListWidgetItem* newUser = new QListWidgetItem(QString::fromUtf8(u.GetUsername().c_str()));
		m_userDisplay->addItem(newUser);
	}

	m_userDisplay->setFont(QFont("8514oem", 13));
	m_userDisplay->show();

	if (m_you.GetAdminRole() == "NonAdmin")
	{
		NonAdminSetUp();
	}
	else
	{
		AdminSetUp();
	}
}

std::string Lobby::GenerateGameCode()
{
	static const std::string_view alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
	static const std::string::size_type length = 5;
	static std::mt19937 rg{ std::random_device{}() };
	static std::uniform_int_distribution<std::string::size_type> choose(0, alphabet.size() - 1);

	std::string code;
	code.reserve(length);
	std::ranges::generate_n(std::back_inserter(code), length, [&]()
		{
			return alphabet[choose(rg)];
		});
	return code;
}

void Lobby::fetchAndUpdateLobby()
{
	std::thread([this]() {
		try {			
			std::vector<PlayerClient> players = PlayerSetUp();
			QMetaObject::invokeMethod(this, [this,players]() {
				UpdateUi(players);
				}, Qt::QueuedConnection);
		}
		catch (const LobbyRequestException& e) {
			qDebug() << "Lobby request exception: " << e.what();
		}
		}).detach();
}

void Lobby::fetchAndUpdateGameState()
{
	std::thread([this]() {
		try {
			while (!stopThreadFlag)
			{
				cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/gamestatus" });

				if (response.error)
				{
					qDebug() << "Player Request failed with error: " << response.error.message;
					qDebug() << "HTTP status code: " << response.status_code;
					throw(PlayerRequestException("FAIL - Player Request"));
				}

				auto gameState = crow::json::load(response.text);

				if (gameState["Gamestatus"].s() == "Playing")
				{
					if (!stopThreadFlag)
					{
						QMetaObject::invokeMethod(this, [this]() {
							UpdateGameState(updateGameStateCalled);
							}, Qt::QueuedConnection);
						updateGameStateCalled = true;
						stopThreadFlag = true;
					}
				}
			}

		}
		catch (const LobbyRequestException& e) {
			qDebug() << "Lobby request exception: " << e.what();
		}
		}).detach();
}

void Lobby::UpdateGameState(bool updateGameStateCalled)
{
	if (m_you.GetAdminRole() == "NonAdmin")
	{
		Client* w = new Client();
		w->You(m_you);
		w->SetDifficulty(0);
		w->SetUi();
		w->GetScribbleArea()->UpdateClient(m_you);
		w->GetScribbleArea()->SetUpUi();
		w->GetPlayerWidget()->SetUi();
		w->GetWordWidget()->GetWordLabel()->setFont(QFont("Sitka Text Semibold", 25));
		w->GetChat()->SetClient(m_you);
		w->GetChat()->SetUi();
		w->show();
		hide();
	}
}

void Lobby::UpdateUi(std::vector<PlayerClient> players)
{
	m_userDisplay->clear();
	for (const auto& p : players)
	{
		QListWidgetItem* newUser = new QListWidgetItem(QString::fromUtf8(p.GetUsername().c_str()));
		m_userDisplay->addItem(newUser);
	}

	m_userDisplay->setFont(QFont("8514oem", 13));
	m_userDisplay->show();

	if (m_you.GetAdminRole() == "NonAdmin")
	{
		NonAdminSetUp();
	}
	else
	{
		AdminSetUp();
	}
}

void Lobby::SendCode()
{
	m_code = GenerateGameCode();
	crow::json::wvalue jsonLoad;
	jsonLoad["code"] = m_code;
	std::string jsonString = jsonLoad.dump();
	cpr::Response r = cpr::Post(cpr::Url("http://localhost:18080/gamecode"), cpr::Body{ jsonString });
	if (r.status_code == 200)
	{
		m_generateCode->hide();
		QLabel* gameCode = new QLabel(this);
		gameCode->setText(QString::fromUtf8(std::string("Room code: " + m_code).c_str()));
		gameCode->setGeometry(100, 150, 200, 30);
		gameCode->setFont(QFont("", 15));
		gameCode->setAlignment(Qt::AlignCenter);
		gameCode->show();
	}
	else
	{
		qDebug() << "\nERROR - couldn't send game code.\n";
	}
}

void Lobby::ShowErrorMessage()
{
	error->show();
	timedError.start();
}

void Lobby::HideErrorMessage()
{
	error->hide();
	timedError.stop();
}

void Lobby::StartGame()
{
	if (m_userDisplay->count() >= 2)
	{
		Difficulty* d = new Difficulty();	
		d->SetClient(m_you);
		d->SendAllClients(m_users);
		d->show();
		hide();
	}
	else
	{
		ShowErrorMessage();
	}
}