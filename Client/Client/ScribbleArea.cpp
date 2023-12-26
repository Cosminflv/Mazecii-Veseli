#include "ScribbleArea.h"
#include <QtWidgets>


ScribbleArea::ScribbleArea(QWidget* parent)
{
	setAttribute(Qt::WA_StaticContents);
	m_isScribbling = false;
	m_penColor = Qt::black;
	m_penWidth = 5;
	int offset = 50;
	int up = 0;

	m_clearButton = new QPushButton("Clear Screen", this);
	m_clearButton->setGeometry(10, 10, 130, 30);
	connect(m_clearButton, &QPushButton::clicked, this, &ScribbleArea::onClearButtonClicked);

	m_selectColor = new QPushButton("More Colors", this);
	m_selectColor->setGeometry(420, 460, 120, 30);
	connect(m_selectColor, &QPushButton::clicked, this, &ScribbleArea::onColorButtonClicked);

	for (const int& size : m_sizes)
	{
		QPushButton* sizeButton = new QPushButton("\u2022", this);
		sizeButton->setFont(QFont("Arial", 23 + up));
		sizeButton->setGeometry(offset + 100, 10, 30, 30);
		connect(sizeButton, &QPushButton::clicked, [this, size]()
			{
				SetPenWidth(size);
			});
		offset += 30 + 10;
		up += 7;
	}

	m_drawing = std::vector < std::vector<std::pair<int, int>>>(
		height(), std::vector<std::pair<int, int>>(width(), std::make_pair(-1, -1)));
}

void ScribbleArea::SetPenColor(const QColor& newColor)
{
	m_penColor = newColor;
	update();
}

void ScribbleArea::SetPenWidth(int newWidth)
{
	m_penWidth = newWidth;
}

QColor ScribbleArea::GetPenColor() const
{
	return m_penColor;
}

int ScribbleArea::GetPenWidth() const
{
	return m_penWidth;
}

std::vector<std::vector<std::pair<int, int>>> ScribbleArea::GetDrawing() const
{
	return m_drawing;
}

void ScribbleArea::DrawInMatrix(int xStart, int yStart, int xEnd, int yEnd)
{
	int xMin = std::min(xStart, xEnd);
	int xMax = std::max(xStart, xEnd);
	int yMin = std::min(yStart, yEnd);
	int yMax = std::max(yStart, yEnd);

	for(int y = yMin; y < yMax; y++)
	{
		for (int x = xMin; x < xMax; x++)
		{
			if (x >= 0 && x < width() && y >= 0 && y < height())
			{
				m_drawing[y][x] == std::make_pair(x, y);
			}
		}
	}
}

void ScribbleArea::ClearDrawingMatrix()
{
	m_drawing = std::vector<std::vector<std::pair<int, int>>>(
		height(), std::vector<std::pair<int, int>>(width(), std::make_pair(-1, -1))
	);
}

void ScribbleArea::PrintMatrix(const QString& output)
{
	QFile file(output);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&file);
		out << m_drawing.size() << "\n";
		for (int i = 0; i < m_drawing.size(); i++)
		{
			for (int j = 0; j < m_drawing.size(); j++)
			{
				out << m_drawing[i][j].first << "," << m_drawing[i][j].second << " | ";
			}
			out << "\n";
		}
	}
	file.close();
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
		DrawLineTo(event->pos());
	}
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && m_isScribbling) {
		DrawLineTo(event->pos());
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
		ResizeImage(&m_image, QSize(newWidth, newHeight));
		update();
	}
	QWidget::resizeEvent(event);
}

void ScribbleArea::DrawLineTo(const QPoint& endPoint)
{
	int xStart = m_lastPoint.x();
	int xEnd = endPoint.x();
	int yStart = m_lastPoint.y();
	int yEnd = endPoint.y();

	//DrawInMatrix(xStart, yStart, xEnd, yEnd);
	//PrintMatrix("coordinates.txt");

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

void ScribbleArea::ResizeImage(QImage* image, const QSize& newSize)
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
	ClearDrawingMatrix();
	m_modified = true;
	update();
}

void ScribbleArea::onColorButtonClicked()
{
	QColor selectedColor = QColorDialog::getColor(m_penColor, this, " ");
	if (selectedColor.isValid())
	{
		SetPenColor(selectedColor);
	}
}

void ScribbleArea::onSelectColor(const QColor& color)
{
	SetPenColor(color);
}
