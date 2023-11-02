#include "ScribbleArea.h"
#include <QtWidgets>

ScribbleArea::ScribbleArea(QWidget* parent)
{
	setAttribute(Qt::WA_StaticContents);
	m_isScribbling = false;
	m_penColor = Qt::red;
	m_penWidth = 5;
}

void ScribbleArea::setPenColor(const QColor& newColor)
{
	m_penColor = newColor;
}

void ScribbleArea::setPenWidth(int newWidth)
{
	m_penWidth = newWidth;
}

QColor ScribbleArea::getPenColor() const
{
	return m_penColor;
}

int ScribbleArea::penWidth() const
{
	return m_penWidth;
}

void ScribbleArea::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		m_lastPoint = event->pos();
		m_isScribbling = true;
	}
}

void ScribbleArea::mouseMoveEvent(QMouseEvent* event)
{
	if ((event->buttons() & Qt::LeftButton) && m_isScribbling) {
		drawLineTo(event->pos());
	}
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && m_isScribbling) {
		drawLineTo(event->pos());
		m_isScribbling = false;
	}
}

void ScribbleArea::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QRect dirtyRect = event->rect();

	painter.drawImage(dirtyRect, m_image, dirtyRect);
}

void ScribbleArea::resizeEvent(QResizeEvent* event)
{
	if (width() > m_image.width() || height() > m_image.height()) {
		int newWidth = qMax(width() + 128, m_image.width());
		int newHeight = qMax(height() + 128, m_image.height());
		resizeImage(&m_image, QSize(newWidth, newHeight));
		update();
	} 
	QWidget::resizeEvent(event);
}

void ScribbleArea::drawLineTo(const QPoint& endPoint)
{
	QPainter painter(&m_image);
	painter.setPen(QPen(m_penColor, m_penWidth, Qt::SolidLine, Qt::RoundCap,
		Qt::RoundJoin));
	painter.drawLine(m_lastPoint, endPoint);
	m_modified = true;

	int rad = (m_penWidth / 2) + 2;
	update(QRect(m_lastPoint, endPoint).normalized()
		.adjusted(-rad, -rad, +rad, +rad));
	m_lastPoint = endPoint;
}

void ScribbleArea::resizeImage(QImage* image, const QSize& newSize)
{
	if (image->size() == newSize)
		return;

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}
