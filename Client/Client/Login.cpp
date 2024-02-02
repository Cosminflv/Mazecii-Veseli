#include "Login.h"
#include <QLabel>
#include "Difficulty.h"
#include "Lobby.h"
#include "EnterCode.h"
#include "PickAction.h"

Login::Login(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFont(QFont("8514oem", 13));
	setWindowTitle("Login");
	setFixedSize(450, 300);	

	QLabel* welcome = new QLabel("Welcome to Gartic", this);
	welcome->setGeometry(70, 30, 340, 50);
	welcome->setFont(QFont("",30));
	QLabel* info = new QLabel("login or create an account to continue", this);
	info->setGeometry(90, 75, 300, 30);
	info->setFont(QFont("", 13));
	info->setStyleSheet("color: gray;");

	m_userText = new QLineEdit(this);
	m_userText->setGeometry(30, 120, 270, 25);
	m_userText->setPlaceholderText("Username");
	m_userText->setFont(QFont("8514oem", 13));
	m_userText->setStyleSheet("background-color: #ffffff");

	m_passwordText = new QLineEdit(this);
	m_passwordText->setGeometry(30, 167, 270, 25);
	m_passwordText->setPlaceholderText("Password");
	m_passwordText->setFont(QFont("8514oem", 13));
	m_passwordText->setStyleSheet("background-color: #ffffff");
	m_passwordText->setEchoMode(QLineEdit::Password);
	QIcon closed("closedeye.png");
	m_showPassword = new QPushButton(this);
	m_showPassword->setIcon(closed);
	m_showPassword->setIconSize(QSize(23, 23));
	m_showPassword->setGeometry(310, 167, 25, 25);
	m_showPassword->setStyleSheet("background-color: #ffffff");
	connect(m_showPassword, &QPushButton::clicked, this, &Login::ShowPassword);


	m_login = new QPushButton("Login", this);
	m_login->setGeometry(330, 210, 100, 30);
	m_login->setFont(QFont("8514oem", 13));
	m_login->setStyleSheet("background-color: #ccd7ff");

	m_createAccount = new QPushButton("Create new account", this);
	m_createAccount->setGeometry(220, 245, 210, 30);
	m_createAccount->setFont(QFont("8514oem", 13));
	m_createAccount->setStyleSheet("background-color: #ccd7ff");

	connect(m_createAccount, &QPushButton::clicked, this, &Login::CreateNewAccount);
	connect(m_login, &QPushButton::clicked, this, &Login::LogintoAccount);

	setStyleSheet("background-color:#edf1ff");	
}

Login::~Login()
{
	delete m_login;
	delete m_createAccount;
	delete m_userText;
	delete m_passwordText;
}

void Login::LogintoAccount()
{
	m_username = m_userText->text().toUtf8().constData();
	m_password = std::to_string(std::hash<std::string> {} (m_passwordText->text().toUtf8().constData()));

	qDebug() << m_username << " " << m_password;
	crow::json::wvalue jsonPayload;
	jsonPayload["username"] = m_username;
	jsonPayload["password"] = m_password;
	std::string jsonString = jsonPayload.dump();
	cpr::Response r = cpr::Post(cpr::Url("http://localhost:18080/logininfo"), cpr::Body{ jsonString });
	if (r.status_code == 200)
	{
		qDebug() << "login data sent.\n";

		crow::json::wvalue json;
		json["Gamestatus"] = "Lobby";
		std::string jsString = json.dump();
		cpr::Response statusResponse = cpr::Post(cpr::Url("http://localhost:18080/gamestatus"), cpr::Body{ jsString });
		if (statusResponse.status_code == 200)
		{
			cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/userinfo" });

			if (response.error)
			{
				throw(PlayerRequestException("FAIL - Player Request"));
			}

			auto serverUsers = crow::json::load(response.text);

			for (const auto& user : serverUsers)
			{
				if (user.has("Username") && user.has("AdminRole"))
				{
					if (user["Username"].t() == crow::json::type::String &&
						user["AdminRole"].t() == crow::json::type::String)
					{
						if (m_username == user["Username"].s())
						{
							m_you.SetUsername(user["Username"].s());
							m_you.SetAdminRole(user["AdminRole"].s());
						}
					}
				}
			}
			PickAction* p = new PickAction();
			p->SetLoginUsername(m_username);
			p->show();
			hide();
		}
	}
	else if (r.status_code == 101)
	{
		QLabel* loginError = new QLabel("invalid data", this);
		loginError->setGeometry(30, 145, 340, 25);
		loginError->setStyleSheet("color: #ab3036;");
		loginError->setFont(QFont("", 9));
		loginError->show();
	}
	else
	{
		qDebug() << "login FAIL\n";
	}
}

void Login::ShowPassword()
{
	QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
	// returns pointer to the obj that sent the signal

	if (senderButton)
	{
		if (senderButton == m_showPassword)
		{
			m_passwordText->setEchoMode(m_passwordText->echoMode() == QLineEdit::Password ? QLineEdit::Normal : QLineEdit::Password);
			QIcon newIcon;
			if (m_passwordText->echoMode() == QLineEdit::Password)
			{
				newIcon = QIcon("closedeye.png");
			}
			else
			{
				newIcon = QIcon("openeye.png");
			}
			m_showPassword->setIcon(newIcon);		
		}
	}
}

void Login::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_Up || e->key() == Qt::Key_Down)
	{
		QWidget* currentWidget = focusWidget();

		// if the current widget is one of the QLineEdit widgets
		if (currentWidget == m_userText || currentWidget == m_passwordText)
		{
			if (currentWidget == m_userText) // switch focus to the other QLineEdit
			{
				m_passwordText->setFocus();
			}
			else
			{
				m_userText->setFocus();
			}
		}
	}
	else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		//enter va face login; pentru create new acc se va apasa manual butonul
		LogintoAccount();
	}
}

void Login::CreateNewAccount()
{
	Register* r = new Register();
	r->show();	
}
