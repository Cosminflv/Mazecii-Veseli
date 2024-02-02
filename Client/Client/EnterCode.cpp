#include "EnterCode.h"
#include "qfontdatabase.h"
#include "crow.h"
#include <cpr/cpr.h>
#include <set>
#include "Lobby.h"

EnterCode::EnterCode(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFont(QFont("8514oem", 20));
	setWindowTitle("Enter Game Code");
	setFixedSize(480, 200);

	int id = QFontDatabase::addApplicationFont(":/fonts/SlopeOpera-gg1Y.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont SlopeOpera(family);
	SlopeOpera.setPointSize(25);

	QLabel* welcome = new QLabel("Enter code to join a game!", this);
	welcome->setGeometry(20, 30, 440, 50);
	welcome->setFont(QFont("", 25));

	m_userText = new QLineEdit(this);
	m_userText->setGeometry(20, 100, 270, 25);
	m_userText->setPlaceholderText("write code here...");
	m_userText->setFont(QFont("8514oem", 13));
	m_userText->setStyleSheet("background-color: #ffffff");

	m_enterGame = new QPushButton("JOIN", this);
	m_enterGame->setGeometry(340, 120, 110, 50);
	m_enterGame->setFont(SlopeOpera);
	m_enterGame->setStyleSheet("background-color:#dfbe9f; color:#660000");
	connect(m_enterGame, &QPushButton::clicked, this, &EnterCode::EnterGame);

	setStyleSheet("background-color:#f9f2ec");
}

EnterCode::~EnterCode()
{}

std::string EnterCode::GetEnteredCode() const
{
	return std::string();
}

void EnterCode::SetLoginUsername(const std::string& username)
{
	this->m_username = username;
}

void EnterCode::EnterGame()
{
	m_code = m_userText->text().toUtf8().constData();
	qDebug() << "\nUSER HAS ENTERED CODE: " << m_code << "\n";
	qDebug() << "USERNAME : " << m_username << "\n";
	std::set<std::string> receivedCodes;

	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/gamecode" });
	auto codesFromServer = crow::json::load(response.text);
	
	if (codesFromServer.has("codes"))
	{
		const auto& codesJSON = codesFromServer["codes"];

		for (const auto& code : codesJSON)
		{
			receivedCodes.insert(code["code"].s());
		}
	}

	if (receivedCodes.find(m_code) != receivedCodes.end())
	{
		crow::json::wvalue json;
		json["user"] = m_username;
		json["signal"] = m_code;
		std::string jsonString = json.dump();
		cpr::Response r = cpr::Post(cpr::Url("http://localhost:18080/codesignal"), cpr::Body{ jsonString });
		if (r.status_code == 200)
		{
			Lobby* lobby = new Lobby();
			lobby->SetLoginUsername(m_username);
			lobby->SetClientARole("NonAdmin");
			lobby->SetUi();
			lobby->show();
			hide();
		}		
	}
	else
	{
		QLabel* error = new QLabel("No game exists with this code!", this);
		error->setGeometry(20, 130, 300, 25);
		error->setFont(QFont("8514oem", 13));
		error->setStyleSheet("color: #ab3036;");
		error->show();
	}
}

void EnterCode::keyPressEvent(QKeyEvent* e)
{
	if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		EnterGame();
	}
}
