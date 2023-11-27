#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Client.h"
#include "ScribbleArea.h"
#include "ChatWidget.h"
#include "TimerWidget.h"
#include "PlayerWidget.h"
#include "ColorWidget.h"

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private:
    Ui::ClientClass ui;
    ScribbleArea* m_scribbleArea;
    ChatWidget* m_chatWidget;
    TimerWidget* m_timerWidget;
    PlayerWidget* m_playerWidget;
    ColorWidget* m_colorWidget;
};
