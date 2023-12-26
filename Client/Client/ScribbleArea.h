#pragma once

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <qpainterpath.h>
#include <QPushButton>
#include <QColorDialog>
#include <vector>

class ScribbleArea : public QWidget
{
public:
	ScribbleArea(QWidget* parent = 0);

	void SetPenColor(const QColor& newColor);
	void SetPenWidth(int newWidth);

	QColor GetPenColor() const;
	int GetPenWidth() const;
	std::vector <std::vector<std::pair<int, int>>> GetDrawing() const;

	void DrawInMatrix(int xStart, int yStart, int xEnd, int yEnd);
	void ClearDrawingMatrix();
	void PrintMatrix(const QString& output);

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
	void DrawLineTo(const QPoint& endPoint);
	void ResizeImage(QImage* image, const QSize& newSize);

	bool m_modified;
	bool m_isScribbling;
	int m_penWidth;

	QColor m_penColor;
	QImage m_image;
	QPoint m_lastPoint;
	QPainterPath mPath;

	QPushButton* m_clearButton;
	QPushButton* m_selectColor;

	std::vector <std::vector<std::pair<int, int>>> m_drawing;

	const QList<int> m_sizes = { 7, 14, 21 };
};

