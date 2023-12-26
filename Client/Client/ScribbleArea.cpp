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

	m_drawing = std::vector<std::pair<int, int>>();

	m_getDrawing = new QPushButton("see drawing", this);
	m_getDrawing->setGeometry(300, 10, 130, 30);
	connect(m_getDrawing, &QPushButton::clicked, this, &ScribbleArea::onGetDrawing);
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

std::vector<std::pair<int, int>> ScribbleArea::GetDrawing() const
{
	return m_drawing;
}

void ScribbleArea::DrawInMatrix(int xStart, int yStart, int xEnd, int yEnd)
{
	int xMin = std::min(xStart, xEnd);
	int xMax = std::max(xStart, xEnd);
	int yMin = std::min(yStart, yEnd);
	int yMax = std::max(yStart, yEnd);

	for (int y = yMin; y <= yMax; y++)
	{
		for (int x = xMin; x <= xMax; x++)
		{
			if (x >= 0 && x < width() && y >= 0 && y < height())
			{
				m_drawing.push_back(std::make_pair(x, y));
			}
		}
	}
}

void ScribbleArea::PrintCoordinates(const QString& output)
{
	QFile file(output);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&file);
		out << m_drawing.size() << "\n";
		for (auto pair : m_drawing)
		{
			out << pair.first << ", " << pair.second << "\n";
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
		int xStart = m_lastPoint.x();
		int xEnd = event->pos().x();
		int yStart = m_lastPoint.y();
		int yEnd = event->pos().y();

		DrawInMatrix(xStart, yStart, xEnd, yEnd);
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
	QPainter painter(&m_image);
	painter.setPen(QPen(m_penColor, m_penWidth, Qt::SolidLine, Qt::RoundCap,
		Qt::RoundJoin));
	painter.drawLine(m_lastPoint, endPoint);
	m_modified = true;

	DrawInMatrix(m_lastPoint.x(), m_lastPoint.y(), endPoint.x(), endPoint.y());

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
	PrintCoordinates("0_coordinates.txt");
	m_drawing.clear();
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

void ScribbleArea::onGetDrawing()
{
	QDialog* drawingDialog = new QDialog(this);
	drawingDialog->setWindowTitle("Drawing Viewer");

	QLabel* label = new QLabel(drawingDialog);
	label->setGeometry(0, 0, this->width(), this->height());

	QPixmap canvas(this->size());
	canvas.fill(Qt::white);
	QPainter painter(&canvas);
	painter.setRenderHint(QPainter::Antialiasing, true);

	for (const auto& point : m_drawing)
	{
		int x = point.first;
		int y = point.second;
		painter.drawPoint(x, y);
	}

	label->setPixmap(canvas);
	label->setAlignment(Qt::AlignCenter);

	QVBoxLayout* layout = new QVBoxLayout(drawingDialog);
	layout->addWidget(label);

	drawingDialog->setLayout(layout);
	drawingDialog->exec();
}
