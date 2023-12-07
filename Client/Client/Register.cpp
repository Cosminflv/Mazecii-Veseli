#include "Register.h"

Register::Register(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("Create Account");
}

Register::~Register()
{
}

void Register::on_pushButton_Register_Clicked()
{
	QString username = ui.lineEdit_username->text();
	QString password = ui.lineEdit_password->text();
}
