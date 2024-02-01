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
#include "PlayerClient.h"
#include <iostream>
#include <numeric>

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

    void SetUi();

    ChatWidget* GetChat() const;
    WordWidget* GetWordWidget() const;
    PlayerWidget* GetPlayerWidget() const;
    PlayerClient YourInstance() const;
    uint16_t GetDifficulty() const;
    ScribbleArea* GetScribbleArea() const;

    void SetDifficulty(const uint16_t& difficulty);
    void SetYourUsername(const std::string& username);
    void You(const PlayerClient& you);

private:
    void AddWidgets();

private:
    Ui::ClientClass ui;

    PlayerClient m_you;

    ScribbleArea* m_scribbleArea;
    ChatWidget* m_chatWidget;
    TimerWidget* m_timerWidget;
    PlayerWidget* m_playerWidget;
    ColorWidget* m_colorWidget;
    WordWidget* m_wordWidget;

    uint16_t m_difficulty;
};
