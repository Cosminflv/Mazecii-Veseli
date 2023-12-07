#include "ScribbleArea.h"
#include <QtWidgets>


ScribbleArea::ScribbleArea(QWidget* parent)
{
	setAttribute(Qt::WA_StaticContents);
	m_isScribbling = false;
	m_penColor = Qt::black;
	m_penWidth = 5;

	m_clearButton = new QPushButton("Clear Screen", this);
	m_clearButton->setGeometry(10, 10, 100, 30);
	connect(m_clearButton, &QPushButton::clicked, this, &ScribbleArea::onClearButtonClicked);

	m_selectColor = new QPushButton("More Colors", this);
	m_selectColor->setGeometry(440, 460, 100, 30);
	connect(m_selectColor, &QPushButton::clicked, this, &ScribbleArea::onColorButtonClicked);
}

void ScribbleArea::setPenColor(const QColor& newColor)
{
	m_penColor = newColor;
	update();
}

void ScribbleArea::setPenWidth(int newWidth)
{
	m_penWidth = newWidth;
}

QColor ScribbleArea::getPenColor() const
{
	return m_penColor;
}

int ScribbleArea::getPenWidth() const
{
	return m_penWidth;
}

ScribbleArea::~ScribbleArea()
{
	delete m_clearButton;
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

void ScribbleArea::onClearButtonClicked() {
	m_image.fill(qRgb(255, 255, 255));
	m_modified = true;
	update();
}

void ScribbleArea::onColorButtonClicked()
{
	QColor selectedColor = QColorDialog::getColor(m_penColor, this, " ");
	if (selectedColor.isValid())
	{
		setPenColor(selectedColor);
	}
}

void ScribbleArea::onSelectColor(const QColor& color)
{
	setPenColor(color);
}
