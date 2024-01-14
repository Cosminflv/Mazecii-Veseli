#pragma once

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QTimer>
#include <qpainterpath.h>
#include <QPushButton>
#include <QColorDialog>
#include "PlayerClient.h"
#include <vector>
#include"crow.h"
#include<cpr/cpr.h>

using Coordinate = std::pair<int, int>;
using DrawingInfo = std::pair<std::string, int>;

class ScribbleArea : public QWidget
{
public:
	ScribbleArea(QWidget* parent = 0);

	void SetUpUi();
	void ResizeImage(QImage* image, const QSize& newSize);
	PlayerClient GetClient() const;
	void UpdatePlayerRole(const std::string& role);
	void UpdateClient(const PlayerClient& you);

	void SetPenColor(const QColor& newColor);
	void SetPenWidth(int newWidth);

	QColor GetPenColor() const;
	int GetPenWidth() const;
	std::vector<Coordinate> GetDrawing() const;

	void DrawInMatrix(int x, int y);
	void PrintCoordinates(const QString& output);

	void SendToSever();
	void UpdateDrawingUI();
	void DrawFromServer();

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

	PlayerClient m_you;

	bool m_isScribbling;
	int m_penWidth;

	std::string m_colorCode;
	QColor m_penColor;
	QImage m_image;
	QPainterPath m_path;

	QPoint m_lastPoint;

	QPushButton* m_clearButton;
	QPushButton* m_selectColor;
	QPushButton* m_getDrawing;

	QTimer* m_timer;

	std::vector<Coordinate> m_drawing;
	std::vector<DrawingInfo> m_info;

	const QList<int> m_sizes = { 6, 14, 21 };
};

