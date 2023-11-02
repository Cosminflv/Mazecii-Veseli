#include "GarticApp.h"

GarticApp::GarticApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);

    setWindowTitle(tr("Scribble"));
    //resize(500, 500);
}

GarticApp::~GarticApp()
{
    delete scribbleArea;
}
