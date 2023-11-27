#pragma once

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <qpainterpath.h>
#include <QPushButton>
#include <QColorDialog>
#include "ColorWidget.h"

class ScribbleArea : public QWidget
{
public:
	ScribbleArea(QWidget* parent = 0);

	void setPenColor(const QColor& newColor);
	void setPenWidth(int newWidth);

	QColor getPenColor() const;
	int getPenWidth() const;

	~ScribbleArea();
private slots:
	void onClearButtonClicked();
	void onColorButtonClicked();
	void onSelectColor(const QColor& color);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	void drawLineTo(const QPoint& endPoint);
	void resizeImage(QImage* image, const QSize& newSize);

	bool m_modified;
	bool m_isScribbling;
	int m_penWidth;

	QColor m_penColor;
	QImage m_image;
	QPoint m_lastPoint;
	QPainterPath mPath;

	QPushButton* m_clearButton;
	QPushButton* m_selectColor;

	ColorWidget* m_colorWidget;
};

