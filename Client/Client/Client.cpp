#include "Client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    m_scribbleArea = new ScribbleArea;
    m_chatWidget = new ChatWidget;

    QSplitter* splitter = new QSplitter(Qt::Horizontal); // Create a horizontal splitter

    splitter->addWidget(m_scribbleArea);
    splitter->addWidget(m_chatWidget);

    setCentralWidget(splitter); // Set the splitter as the central widget

    setWindowTitle(tr("Scribble"));
}

Client::~Client()
{
    delete m_scribbleArea;
    delete m_chatWidget;
}
