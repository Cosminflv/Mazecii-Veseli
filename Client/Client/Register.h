#pragma once

#include <QMainWindow>
#include <Qlabel>
#include <QLineEdit>
#include <QPushButton>
#include <regex>
#include "ui_Register.h"
#include "ClientExceptions.h"


class Register : public QMainWindow
{
	Q_OBJECT

public:
	Register(QWidget *parent = nullptr);
	~Register();

	std::string GetUsername() const;
	std::string GetPassword() const;

	bool PasswordValidation();
	bool AccountCreated();

private slots:
	void CreateAccount();
	void ShowPasswordText();

protected:
	void keyPressEvent(QKeyEvent* e) override;

private:
	Ui::RegisterClass ui;

	QPushButton* m_create;
	QPushButton* m_showPassword;
	QPushButton* m_showConfirm;

	QLineEdit* m_userText;
	QLineEdit* m_passwordText;
	QLineEdit* m_confirmPassword;

	QLabel* m_passwordError;

	std::string m_username;
	std::string m_password;
	bool m_accountCreated;
};
