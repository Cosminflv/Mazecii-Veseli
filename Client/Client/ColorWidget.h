#pragma once
#include <QtWidgets>
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
        "#000000", // Qt::black
        "#FF0000", // Qt::red
        "#00FF00", // Qt::green
        "#66ccff", // blue
        "#ffff00", // Qt::yellow
        "#ff3399", //pink
        "#804000", // brown
        "#FFFFFF", // Qt::white
        "#b30000", // dark red       
        "#006600", // dark green       
        "#0047b3",  //dark blue       
        "#ff9933", // orange        
        "#9966ff", //purple       
        "#4d4d4d"  //gray
    };
};
