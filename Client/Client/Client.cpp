#include "Client.h"

Client::Client(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    m_scribbleArea = new ScribbleArea;
    m_chatWidget = new ChatWidget;
    m_timerWidget = new TimerWidget;

    QGridLayout* mainLayout = new QGridLayout(this);

    mainLayout->addWidget(m_timerWidget, 0, 0);
    mainLayout->addWidget(m_scribbleArea, 1, 0);
    mainLayout->addWidget(m_chatWidget, 1, 1);

    mainLayout->setColumnStretch(0, 5);
    mainLayout->setColumnStretch(1, 2);

    QWidget* centralWidget = new QWidget(this);

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);

    setWindowTitle(tr("Scribble"));
}

Client::~Client()
{
    delete m_scribbleArea;
    delete m_chatWidget;
    delete m_timerWidget;
}
