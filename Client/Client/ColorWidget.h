#pragma once
#include <QtWidgets>
#include <QPushButton>
#include <QColorDialog>

class ColorWidget : public QWidget
{
    Q_OBJECT

public:
    ColorWidget(QWidget* parent = nullptr);

signals:
    void selectColor(const QColor& color);

private:

    const QStringList m_colors =
    {
        "#000000", // black
        "#e60000", // red
        "#47d147", // green
        "#66ccff", // blue
        "#ffdb4d", // yellow
        "#ff3399", // pink
        "#804000", // brown
        "#ffffff", // white
        "#b30000", // dark red       
        "#006600", // dark green       
        "#0047b3", // dark blue       
        "#ff9933", // orange        
        "#aa80ff", // purple       
        "#4d4d4d"  // gray
    };
};
