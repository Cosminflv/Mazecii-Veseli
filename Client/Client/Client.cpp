#include "Client.h"
#include "ClientExceptions.h"

Client::Client(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle(tr("Scribble"));
  
    m_scribbleArea = new ScribbleArea;  
    m_scribbleArea->SetUpUi();
    m_chatWidget = new ChatWidget;
    m_timerWidget = new TimerWidget;
    m_playerWidget = new PlayerWidget;
    m_colorWidget = new ColorWidget;
    m_wordWidget = new WordWidget;

    m_scribbleArea->setFixedHeight(500);
    m_chatWidget->setFixedHeight(510);
    m_playerWidget->setFixedHeight(400);
    m_colorWidget->setFixedHeight(100);
    m_wordWidget->setFixedSize(300, 50);

    m_wordWidget->FetchTheWord(m_difficulty);

    connect(m_timerWidget, &TimerWidget::timerUpdate, [this](const QString& timeString, const QPalette& textColor)
        {
            m_timerWidget->GetTimeLabel()->setText(timeString);
            m_timerWidget->GetTimeLabel()->setPalette(textColor);
        });
    connect(m_chatWidget, &ChatWidget::messageSent, [this]() {
        QTimer::singleShot(500, this, [this]() {
            m_playerWidget->UpdateScoreUI(m_you.GetUsername());
            });
        });
}

void Client::AddWidgets()
{
    QGridLayout* mainLayout = new QGridLayout(this);
    setFont(QFont("8514oem", 13));
    setStyleSheet("background-color: #eaeafa");
    mainLayout->addWidget(m_timerWidget, 0, 0, 1, 3);
    mainLayout->addWidget(m_playerWidget, 1, 0);
    mainLayout->addWidget(m_scribbleArea, 1, 1, 2, 1);
    if(m_you.GetPlayerRole() == "Painter")
        mainLayout->addWidget(m_colorWidget, 2, 0);
    mainLayout->addWidget(m_chatWidget, 1, 2, 3, 1);
    mainLayout->addWidget(m_wordWidget, 0, 1, 1, 3);
    mainLayout->setAlignment(m_wordWidget, Qt::AlignCenter);
    mainLayout->setColumnStretch(0, 4);
    mainLayout->setColumnStretch(1, 11);
    mainLayout->setColumnStretch(2, 5);
    mainLayout->setRowStretch(0, 1);
    mainLayout->setRowStretch(1, 3);
    mainLayout->setRowStretch(2, 2);
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void Client::SetUi()
{
    if (m_you.GetPlayerRole() == "Painter")
    {
        setWindowTitle(tr("PAINT!"));
        m_scribbleArea->UpdatePlayerRole("Painter");      
        connect(m_colorWidget, &ColorWidget::selectColor, m_scribbleArea, &ScribbleArea::SetPenColor);
        m_wordWidget->UpdateWord(m_wordWidget->FetchSeenWordFromServer(m_difficulty));
    }
    else if (m_you.GetPlayerRole() == "Guesser")
    {
        setWindowTitle(tr("GUESS!"));
        setFont(QFont("8514oem", 13));
        setStyleSheet("background-color: #eaeafa");
        m_scribbleArea->UpdatePlayerRole("Guesser");
        connect(m_timerWidget, &TimerWidget::wordUpdated, m_wordWidget, &WordWidget::UpdateWordFromServer);
        m_wordWidget->UpdateWord(m_wordWidget->FetchUpdatedWordFromServer());
    }
    AddWidgets();
}

Client::~Client()
{
    delete m_scribbleArea;
    delete m_chatWidget;
    delete m_timerWidget;
    delete m_playerWidget;
    delete m_colorWidget;
    delete m_wordWidget;
}

ChatWidget* Client::GetChat() const
{
    return m_chatWidget;
}

WordWidget* Client::GetWordWidget() const
{
    return m_wordWidget;
}

PlayerWidget* Client::GetPlayerWidget() const
{
    return m_playerWidget;
}

PlayerClient Client::YourInstance() const
{
    return m_you;
}

uint16_t Client::GetDifficulty() const
{
    return m_difficulty;
}

ScribbleArea* Client::GetScribbleArea() const
{
    return m_scribbleArea;
}

void Client::SetDifficulty(const uint16_t& difficulty)
{
    m_difficulty = difficulty;
}

void Client::SetYourUsername(const std::string& username)
{
    m_you.SetUsername(username);
}

void Client::You(const PlayerClient& you)
{
    m_you.SetUsername(you.GetUsername());
    m_you.SetAdminRole(you.GetAdminRole());
    m_you.UpdatePlayerRole(you.GetPlayerRole());
    m_you.UpdateScore(you.GetScore());
    m_you.UpdateStatus(you.GetStatus());
}

