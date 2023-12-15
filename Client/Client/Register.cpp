#include "Register.h"
#include"crow.h"
#include<cpr/cpr.h>
#include "Client.h"

Register::Register(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("Create Account");
	setFixedSize(450, 300);

	QLabel* welcome = new QLabel("\t\tSign up", this);
	welcome->setGeometry(60, 30, 400, 50);

	QLabel* username = new QLabel("Create Username: ", this);
	username->setGeometry(30, 100, 130, 30);
	m_userText = new QLineEdit(this);
	m_userText->setGeometry(170, 100, 210, 25);

	QLabel* password = new QLabel("Create Password: ", this);
	password->setGeometry(30, 140, 130, 30);
	m_passwordText = new QLineEdit(this);
	m_passwordText->setGeometry(170, 140, 210, 25);

	m_create = new QPushButton("Create account", this);
	m_create->setGeometry(130, 220, 210, 30);

	connect(m_create, &QPushButton::clicked, this, &Register::CreateAccount);
}

Register::~Register()
{
	delete m_userText;
	delete m_passwordText;
	delete m_create;
}

std::string Register::GetUsername() const
{
	return m_username;
}

std::string Register::GetPassword() const
{
	return m_password;
}

bool Register::PasswordValidation()
{
	// password of at least 6 letters and at least one number
	std::regex validForm("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{6,}$");

	if (std::regex_match(m_password, validForm))
	{
		qDebug() << " \nVALID.\n";
		return true;
	}
	else
	{
		qDebug() << "\nINVALID PASSWORD.\n";
		return false;
	}
}

bool Register::AccountCreated()
{
	return m_accountCreated;
}

void Register::CreateAccount()
{
	m_username = m_userText->text().toUtf8().constData();
	m_password = m_passwordText->text().toUtf8().constData();

	if (PasswordValidation())
	{
		qDebug() << m_username << " " << m_password;
		//impachetez campuri
		crow::json::wvalue jsonPayload;
		jsonPayload["username"] = m_username;
		jsonPayload["password"] = m_password;
		std::string jsonString = jsonPayload.dump();
		cpr::Response r = cpr::Post(cpr::Url("http://localhost:18080/registerinfo"), cpr::Body{ jsonString });
		m_accountCreated = true;
		if (r.status_code == 200)
		{
			qDebug() << "register data sent.\n";
			Client* w = new Client();
			w->show();
			w->GetChat()->SetClientUsername(m_username);
		}
		else
		{
			qDebug() << "register FAIL\n";
		}
	}
	else
	{
		throw(PasswordException("Invalid password."));
	}
}

