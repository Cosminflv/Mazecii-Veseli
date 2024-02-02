#include "PickAction.h"

PickAction::PickAction(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFont(QFont("8514oem", 20));
	setWindowTitle("Pick Action");
	setFixedSize(300, 130);

	m_create = new QPushButton("Create Room", this);
	m_create->setGeometry(50, 20, 200, 40);
	m_create->setFont(QFont("", 17));
	m_create->setStyleSheet("background-color: #b198b3;color:#483649;");
	connect(m_create, &QPushButton::clicked, this, &PickAction::CreateRoom);

	m_join = new QPushButton("Join Room", this);
	m_join->setGeometry(50, 70, 200, 40);
	m_join->setFont(QFont("", 17));
	m_join->setStyleSheet("background-color:#bfcbb4;color:#4d5a3f;");
	connect(m_join, &QPushButton::clicked, this, &PickAction::JoinRoom);

	setStyleSheet("background-color:#f5f0f0;");
}

PickAction::~PickAction()
{}

void PickAction::SetLoginUsername(const std::string & username)
{
	m_loginUsername = username;
}

void PickAction::CreateRoom()
{
	Lobby* lobby = new Lobby();
	lobby->SetLoginUsername(m_loginUsername);
	lobby->SetClientARole("Admin");
	lobby->SetUi();
	lobby->show();
	hide();
}

void PickAction::JoinRoom()
{
	EnterCode* e = new EnterCode();
	e->SetLoginUsername(m_loginUsername);
	e->show();
	hide();
}
