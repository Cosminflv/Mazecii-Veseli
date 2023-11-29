#include "Client.h"
#include <QtWidgets/QApplication>
#include <cpr/cpr.h>
#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <crow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.show();
    return a.exec();
}
