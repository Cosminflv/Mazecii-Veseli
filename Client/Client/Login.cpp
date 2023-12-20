#include "Login.h"

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

	m_userText = new QLineEdit(this);
	m_userText->setGeometry(30, 100, 270, 25);
	m_userText->setPlaceholderText("Username");

	m_passwordText = new QLineEdit(this);
	m_passwordText->setGeometry(30, 140, 270, 25);
	m_passwordText->setPlaceholderText("Password");
	m_passwordText->setEchoMode(QLineEdit::Password);
	m_showPassword = new QPushButton("s", this);
	m_showPassword->setGeometry(310, 140, 25, 25);
	connect(m_showPassword, &QPushButton::clicked, this, &Login::ShowPassword);


	m_login = new QPushButton("Login", this);
	m_login->setGeometry(320, 190, 100, 30);

	m_createAccount = new QPushButton("Create new account", this);
	m_createAccount->setGeometry(210, 230, 210, 30);

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
