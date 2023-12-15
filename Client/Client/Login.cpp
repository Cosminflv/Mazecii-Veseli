#include "Login.h"

Login::Login(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle("Login");
	setFixedSize(450, 300);	

	QLabel* welcome = new QLabel("\t       Welcome to Gartic!\nPlease login or create an account to continue!", this);
	welcome->setGeometry(60, 30, 400, 50);

	QLabel* username = new QLabel("Username: ", this);
	username->setGeometry(30, 100, 100, 30);
	m_userText = new QLineEdit(this);
	m_userText->setGeometry(150, 100, 210, 25);
	
	QLabel* password = new QLabel("Password: ", this);
	password->setGeometry(30, 140, 100, 30);
	m_passwordText = new QLineEdit(this);
	m_passwordText->setGeometry(150, 140, 210, 25);	

	m_login = new QPushButton("Login", this);
	m_login->setGeometry(180, 180, 100, 30);

	m_createAccount = new QPushButton("Create new account", this);
	m_createAccount->setGeometry(130, 220, 210, 30);

	connect(m_createAccount, &QPushButton::clicked, this, &Login::CreateNewAccount);
	connect(m_login, &QPushButton::clicked, this, &Login::LogintoAccount);
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
	m_password = m_passwordText->text().toUtf8().constData();

	qDebug() << m_username << " " << m_password;
}

void Login::CreateNewAccount()
{
	Register* r = new Register();
	r->show();	
}
