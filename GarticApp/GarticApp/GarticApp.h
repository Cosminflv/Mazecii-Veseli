#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GarticApp.h"

class GarticApp : public QMainWindow
{
    Q_OBJECT

public:
    GarticApp(QWidget *parent = nullptr);
    ~GarticApp();

private:
    Ui::GarticAppClass ui;
};
