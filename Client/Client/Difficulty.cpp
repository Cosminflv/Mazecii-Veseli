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

std::string Difficulty::GetLoginUsername() const
{
	return m_you.GetUsername();
}

void Difficulty::SetLoginUsername(const std::string& username)
{
	m_you.SetUsername(username);
}

std::vector<PlayerClient> Difficulty::GetClients() const
{
	return m_clientsToPass;
}

PlayerClient Difficulty::GetClient() const
{
	return m_you;
}

void Difficulty::SendAllClients(const std::vector<PlayerClient>& clients)
{
	m_clientsToPass = clients;
}

void Difficulty::SetSendDifficulty(const uint16_t& d)
{
	m_difficulty = d;
}

void Difficulty::SetClient(const PlayerClient& client)
{
	m_you.SetUsername(client.GetUsername());
	m_you.SetAdminRole(client.GetAdminRole());
	m_you.UpdatePlayerRole(client.GetPlayerRole());
	m_you.UpdateScore(client.GetScore());
	m_you.UpdateStatus(client.GetStatus());
}

uint16_t Difficulty::GetDifficultyFromWindow() const
{
	return m_difficulty;
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

	crow::json::wvalue json;
	json["Gamestatus"] = "Playing";
	std::string jsString = json.dump();
	cpr::Response statusResponse = cpr::Post(cpr::Url("http://localhost:18080/gamestatus"), cpr::Body{ jsString });

	qDebug() << m_difficulty;
	Client* w = new Client();
	w->You(m_you);
	w->SetDifficulty(m_difficulty);
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
