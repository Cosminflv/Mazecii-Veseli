#pragma once
#include <WinSock2.h>
#include <QtWidgets/QMainWindow>
#include "ui_Client.h"
#include "ScribbleArea.h"
#include "ChatWidget.h"
#include "TimerWidget.h"
#include "PlayerWidget.h"
#include "ColorWidget.h"
#include "WordWidget.h"
#include <iostream>
#include <numeric>

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

    ChatWidget* GetChat() const;
    WordWidget* GetWordWidget() const;

    uint16_t GetDifficulty() const;
    void SetDifficulty(const uint16_t& difficulty);

private:
    Ui::ClientClass ui;
    ScribbleArea* m_scribbleArea;
    ChatWidget* m_chatWidget;
    TimerWidget* m_timerWidget;
    PlayerWidget* m_playerWidget;
    ColorWidget* m_colorWidget;
    WordWidget* m_wordWidget;

    uint16_t m_difficulty;
};
