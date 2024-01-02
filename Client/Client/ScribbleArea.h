#pragma once

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <qpainterpath.h>
#include <QPushButton>
#include <QColorDialog>
#include <vector>
#include"crow.h"
#include<cpr/cpr.h>

using Coordinate = std::pair<int, int>;
using DrawingInfo = std::pair<std::string, int>;

class ScribbleArea : public QWidget
{
public:
	ScribbleArea(QWidget* parent = 0);

	void SetPenColor(const QColor& newColor);
	void SetPenWidth(int newWidth);

	QColor GetPenColor() const;
	int GetPenWidth() const;
	std::vector<Coordinate> GetDrawing() const;

	void DrawInMatrix(int x, int y);
	void PrintCoordinates(const QString& output);

	void SendToSever();

	~ScribbleArea();
private slots:
	void onClearButtonClicked();
	void onColorButtonClicked();
	void onSelectColor(const QColor& color);
	void onGetDrawing();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	void DrawLineTo(const QPoint& endPoint);
	void ResizeImage(QImage* image, const QSize& newSize);

	bool m_modified;
	bool m_isScribbling;
	int m_penWidth;

	std::string m_colorCode;
	QColor m_penColor;
	QImage m_image;
	QPoint m_lastPoint;
	QPainterPath m_path;

	QPushButton* m_clearButton;
	QPushButton* m_selectColor;
	QPushButton* m_getDrawing;

	std::vector<Coordinate> m_drawing;
	std::vector<DrawingInfo> m_info;

	const QList<int> m_sizes = { 7, 14, 21 };
};

