//#include "Client.h"
//#include "Register.h"
#include "Login.h"
#include "Client.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include "Difficulty.h"
#include "Lobby.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Login l;
	l.show();
	//Client c;
	//c.show();
	return a.exec();
}
