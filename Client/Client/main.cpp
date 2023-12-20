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

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Login l;
	l.show();
	//Client c;
	//c.show();
	//Difficulty d;
	//d.show();
	return a.exec();
}
