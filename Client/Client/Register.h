#pragma once

#include <QMainWindow>
#include <Qlabel>
#include <QLineEdit>
#include <QPushButton>
#include "ui_Register.h"

class Register : public QMainWindow
{
	Q_OBJECT

public:
	Register(QWidget *parent = nullptr);
	~Register();

private slots:
	void on_pushButton_Register_Clicked();

private:
	Ui::RegisterClass ui;
};
