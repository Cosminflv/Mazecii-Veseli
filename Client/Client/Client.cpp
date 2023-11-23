#include "Client.h"

Client::Client(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    m_scribbleArea = new ScribbleArea;
    m_chatWidget = new ChatWidget;
    m_timerWidget = new TimerWidget;
    m_playerWidget = new PlayerWidget;

    QGridLayout* mainLayout = new QGridLayout(this);

    mainLayout->addWidget(m_timerWidget,0, 0);
    mainLayout->addWidget(m_playerWidget, 1, 0);
    mainLayout->addWidget(m_scribbleArea, 1 , 1);
    mainLayout->addWidget(m_chatWidget, 1, 2);

    mainLayout->setColumnStretch(0, 4);
    mainLayout->setColumnStretch(1, 11);
    mainLayout->setColumnStretch(2, 5);
    mainLayout->setRowStretch(1, 1);
    
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle(tr("Scribble"));

    connect(m_timerWidget, &TimerWidget::timerUpdate, [this](const QString& timeString, const QPalette& textColor)
        {
            m_timerWidget->GetTimeLabel()->setText(timeString);
            m_timerWidget->GetTimeLabel()->setPalette(textColor);
        });

}

Client::~Client()
{
    delete m_scribbleArea;
    delete m_chatWidget;
    delete m_timerWidget;
}
