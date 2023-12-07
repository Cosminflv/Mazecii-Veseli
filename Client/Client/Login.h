#pragma once

#include <QMainWindow>
#include "ui_Login.h"
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>

class Login : public QMainWindow
{
	Q_OBJECT

public:
	Login(QWidget *parent = nullptr);
	~Login();

private:
	Ui::LoginClass ui;

	QGroupBox* m_loginWindow;
	QPushButton* m_login;
	QPushButton* m_createAccount;
	QLineEdit* m_userText;
	QLineEdit* m_passwordText;
};
