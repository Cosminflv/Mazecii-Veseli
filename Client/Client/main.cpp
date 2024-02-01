#include "Login.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include "EnterCode.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Login l;
	l.show();
	return a.exec();
}
