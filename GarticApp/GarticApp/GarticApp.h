#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GarticApp.h"
#include "ScribbleArea.h"
#include "MyBoardWidget.cpp"

class GarticApp : public QMainWindow
{
    Q_OBJECT

public:
    GarticApp(QWidget *parent = nullptr);
    ~GarticApp();

private:
    Ui::GarticAppClass ui;
    ScribbleArea* scribbleArea;
    MyBoardWidget* boardArea;
};
