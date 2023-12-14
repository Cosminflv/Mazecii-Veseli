#pragma once

#include <QMainWindow>
#include <Qlabel>
#include <QLineEdit>
#include <QPushButton>
#include <regex>
#include "ui_Register.h"
//#include <cpr/cpr.h>
//#include "crow.h"

class Register : public QMainWindow
{
	Q_OBJECT

public:
	Register(QWidget *parent = nullptr);
	~Register();

	void PasswordValidation();

private slots:
	void CreateAccount();


private:
	Ui::RegisterClass ui;

	QPushButton* m_create;
	QLineEdit* m_userText;
	QLineEdit* m_passwordText;

	std::string m_username;
	std::string m_password;
};
