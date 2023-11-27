#include "ColorWidget.h"

ColorWidget::ColorWidget(QWidget* parent)
{
    QGridLayout* layout = new QGridLayout(this);

    int row = 0;
    int col = 0;
    for (const QString& colorCode : m_colors)
    {
        QColor color(colorCode);
        QPushButton* colorButton = new QPushButton(this);
        colorButton->setFixedSize(30, 30);
        colorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        connect(colorButton, &QPushButton::clicked, this, [this, color]()
            {
                emit selectColor(color);
            });

        layout->addWidget(colorButton, row, col);
        col++;
        if (col >= 7) {
            col = 0;
            row++;
        }
    }
}
