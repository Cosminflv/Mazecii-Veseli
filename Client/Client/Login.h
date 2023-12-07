#pragma once

#include <QMainWindow>
#include "ui_Login.h"
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>

class Login : public QMainWindow
{
	Q_OBJECT

public:
	Login(QWidget *parent = nullptr);
	~Login();

private:
	Ui::LoginClass ui;

	QPushButton* m_login;
	QPushButton* m_createAccount;
	QLineEdit* m_userText;
	QLineEdit* m_passwordText;
};
