#include "Register.h"
#include"crow.h"
#include<cpr/cpr.h>
#include "Client.h"
#include "Difficulty.h"

Register::Register(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFont(QFont("8514oem", 13));
	setWindowTitle("Create Account");
	setFixedSize(450, 300);

	QLabel* welcome = new QLabel("Sign up", this);
	welcome->setGeometry(160, 25, 340, 50);
	welcome->setFont(QFont("", 30));

	m_userText = new QLineEdit(this);
	m_userText->setGeometry(30, 90, 270, 25);
	m_userText->setPlaceholderText("Create Username");

	m_passwordText = new QLineEdit(this);
	m_passwordText->setGeometry(30, 130, 270, 25);
	m_passwordText->setPlaceholderText("Create Password");
	m_passwordText->setEchoMode(QLineEdit::Password);
	
	m_showPassword = new QPushButton("s",this);
	m_showPassword->setGeometry(310, 130, 25, 25);
	connect(m_showPassword, &QPushButton::clicked, this, &Register::ShowPasswordText);
	QLabel* password = new QLabel("(must contain at least 6 letters and 1 number)", this);
	password->setGeometry(30, 155, 340, 25);
	password->setStyleSheet("color: gray;");
	password->setFont(QFont("", 9));

	m_confirmPassword = new QLineEdit(this);
	m_confirmPassword->setGeometry(30, 180, 270, 25);
	m_confirmPassword->setPlaceholderText("Confirm Password");
	m_confirmPassword->setEchoMode(QLineEdit::Password);
	m_showConfirm = new QPushButton("s", this);
	m_showConfirm->setGeometry(310, 180, 25, 25);
	connect(m_showConfirm, &QPushButton::clicked, this, &Register::ShowPasswordText);

	m_create = new QPushButton("Create account", this);
	m_create->setGeometry(210, 240, 210, 30);

	connect(m_create, &QPushButton::clicked, this, &Register::CreateAccount);
	setStyleSheet("background-color:#f0efff"); 
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

void Register::ShowPasswordText()
{
	QPushButton* senderButton = qobject_cast<QPushButton*>(sender());

	if (senderButton)
	{
		if (senderButton == m_showPassword)
		{
			m_passwordText->setEchoMode(m_passwordText->echoMode() == QLineEdit::Password ? QLineEdit::Normal : QLineEdit::Password);
		}
		else if (senderButton == m_showConfirm)
		{
			m_confirmPassword->setEchoMode(m_confirmPassword->echoMode() == QLineEdit::Password ? QLineEdit::Normal : QLineEdit::Password);
		}
	}
}

void Register::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_Up || e->key() == Qt::Key_Down)
	{
		QWidget* currentWidget = focusWidget();

		// if the current widget is one of the QLineEdit widgets
		if (currentWidget == m_userText || currentWidget == m_passwordText || currentWidget == m_confirmPassword)
		{
			if (currentWidget == m_userText) // switch focus to the other QLineEdit
			{
				m_passwordText->setFocus();
			}
			else if (currentWidget == m_passwordText)
			{
				m_confirmPassword->setFocus();
			}
			else
			{
				m_userText->setFocus();
			}
		}
	}
	else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		CreateAccount();
	}
}

void Register::CreateAccount()
{
	m_username = m_userText->text().toUtf8().constData();
	m_password = m_passwordText->text().toUtf8().constData();

	if (PasswordValidation() && m_passwordText->text() == m_confirmPassword->text())
	{
		m_password = std::to_string(std::hash<std::string> {} (m_passwordText->text().toUtf8().constData()));
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
			Difficulty* d = new Difficulty();
			d->show();

			while (!d->DifficultyIsSet())
			{
				QCoreApplication::processEvents();
			}

			if (d->DifficultyIsSet() == true)
			{
				Client* w = new Client();
				w->show();
				w->GetWordWidget()->SetDifficulty(d->GetDifficulty());
				w->GetChat()->SetClientUsername(m_username);
				d->hide();
				hide();
			}
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

