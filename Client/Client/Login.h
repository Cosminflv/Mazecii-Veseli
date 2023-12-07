#pragma once

#include <QMainWindow>
#include "ui_Login.h"
#include "Register.h"
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <string>

class Login : public QMainWindow
{
	Q_OBJECT

public:
	Login(QWidget *parent = nullptr);
	~Login();

private slots:
	void CreateNewAccount();
	void LogintoAccount();

private:
	Ui::LoginClass ui;

	QPushButton* m_login;
	QPushButton* m_createAccount;
	QLineEdit* m_userText;
	QLineEdit* m_passwordText;

	std::string m_username;
	std::string m_password;
};
