#include "Client.h"

Client::Client(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    m_scribbleArea = new ScribbleArea;
    m_chatWidget = new ChatWidget;
    m_timerWidget = new TimerWidget;
    m_playerWidget = new PlayerWidget;
    m_colorWidget = new ColorWidget;

    m_scribbleArea->setFixedHeight(500);
    m_chatWidget->setFixedHeight(500);
    m_playerWidget->setFixedHeight(400);
    m_colorWidget->setFixedHeight(100);

    QGridLayout* mainLayout = new QGridLayout(this);

    mainLayout->addWidget(m_timerWidget, 0, 0, 1, 3); // Row 0, Column 0, Row Span 1, Column Span 3
    mainLayout->addWidget(m_playerWidget, 1, 0);
    mainLayout->addWidget(m_colorWidget, 2, 0);
    mainLayout->addWidget(m_scribbleArea, 1, 1, 2, 1); // Row 1, Column 1, Row Span 2, Column Span 1
    mainLayout->addWidget(m_chatWidget, 1, 2, 3, 1); // Row 0, Column 2, Row Span 3, Column Span 1

    mainLayout->setColumnStretch(0, 4);
    mainLayout->setColumnStretch(1, 11);
    mainLayout->setColumnStretch(2, 5);
    mainLayout->setRowStretch(0, 1);
    mainLayout->setRowStretch(1, 3);
    mainLayout->setRowStretch(2, 2);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle(tr("Scribble"));

    connect(m_timerWidget, &TimerWidget::timerUpdate, [this](const QString& timeString, const QPalette& textColor)
        {
            m_timerWidget->GetTimeLabel()->setText(timeString);
            m_timerWidget->GetTimeLabel()->setPalette(textColor);
        });

    connect(m_colorWidget, &ColorWidget::selectColor, m_scribbleArea, &ScribbleArea::setPenColor);
}

Client::~Client()
{
    delete m_scribbleArea;
    delete m_chatWidget;
    delete m_timerWidget;
    delete m_colorWidget;
}