#include "Client.h"
#include "Register.h"
#include <QtWidgets/QApplication>
#include <cpr/cpr.h>
#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <crow.h>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Client w;
	w.show();
	Register r;
	r.show();
	return a.exec();
}
