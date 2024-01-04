#include "ScribbleArea.h"
#include <QtWidgets>
#include <QJsonDocument>
#include <QJsonObject>
#include <future>

ScribbleArea::ScribbleArea(QWidget* parent)
	: QGraphicsView(parent), m_scene(new QGraphicsScene(this)), m_currentLine(nullptr),
	m_isScribbling(false), m_colorCode("#000000"), m_penWidth(6),
	m_penColor(QString::fromUtf8(m_colorCode.c_str()))
{
	setAttribute(Qt::WA_StaticContents);
	setRenderHint(QPainter::Antialiasing, true);
	m_scene->setSceneRect(0, 0, width(), height());
	setScene(m_scene);

	int offset = 50;
	int up = 0;

	m_clearButton = new QPushButton("Clear Screen", this);
	m_clearButton->setGeometry(10, 10, 130, 30);
	connect(m_clearButton, &QPushButton::clicked, this, &ScribbleArea::onClearButtonClicked);

	m_selectColor = new QPushButton("More Colors", this);
	m_selectColor->setGeometry(420, 440, 120, 30);
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

	m_drawing = std::vector<Coordinate>();

	m_getDrawing = new QPushButton("see drawing", this);
	m_getDrawing->setGeometry(300, 10, 130, 30);
	connect(m_getDrawing, &QPushButton::clicked, this, &ScribbleArea::onGetDrawing);

	m_timer = new QTimer(this);
	m_timer->setInterval(300);
	m_timer->start();
	connect(m_timer, &QTimer::timeout, this, &ScribbleArea::SendToSever);
}

void ScribbleArea::SetPenColor(const QColor& newColor)
{
	m_penColor = newColor;
	m_colorCode = newColor.name().toUtf8().constData();
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

std::vector<Coordinate> ScribbleArea::GetDrawing() const
{
	return m_drawing;
}

void ScribbleArea::DrawInMatrix(int x, int y)
{
	if (x >= 0 && x < width() && y >= 0 && y < height())
	{
		m_drawing.push_back(std::make_pair(x, y));
		m_info.push_back(std::make_pair(m_colorCode, m_penWidth));
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

void ScribbleArea::SendToSever()
{
	std::thread([this]() {
		try {
			crow::json::wvalue jsonVectors;
			crow::json::wvalue::list coordinatesVect;
			crow::json::wvalue::list infoVect;

			for (const auto& coordinate : m_drawing)
			{
				crow::json::wvalue obj;
				obj["first"] = coordinate.first;
				obj["second"] = coordinate.second;
				coordinatesVect.push_back(obj);
			}

			jsonVectors["Coordinates"] = std::move(coordinatesVect);

			for (const auto& info : m_info)
			{
				crow::json::wvalue obj;
				obj["first"] = info.first;
				obj["second"] = info.second;
				infoVect.push_back(obj);
			}

			jsonVectors["DrawingInfo"] = std::move(infoVect);
			std::string jsonString = jsonVectors.dump();
			cpr::Response response = cpr::Post(cpr::Url("http://localhost:18080/drawing"), cpr::Body{ jsonString });

			if (response.status_code == 200)
			{
				qDebug() << "DRAWING SENT.";
			}
			else
			{
				qDebug() << "FAIL - DRAWING.";
			}
		}
		catch (const std::exception& e) {

			qDebug() << "Exception in SendToServer: " << e.what();
		}
		}).detach();
}

ScribbleArea::~ScribbleArea()
{
	delete m_clearButton;
	delete m_currentLine;
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
	if ((event->buttons() & Qt::LeftButton) && m_isScribbling)
	{
		DrawLineTo(event->pos());
		DrawInMatrix(event->pos().x(), event->pos().y());
	}
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && m_isScribbling) {
		DrawLineTo(event->pos());
		m_isScribbling = false;
	}
}

void ScribbleArea::DrawLineTo(const QPointF& endPoint)
{

	QGraphicsLineItem* newLine = new QGraphicsLineItem();
	newLine->setPen(QPen(m_penColor, m_penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	newLine->setLine(QLineF(m_lastPoint, endPoint));
	m_scene->addItem(newLine);

	DrawInMatrix(m_lastPoint.x(), m_lastPoint.y());
	DrawInMatrix(endPoint.x(), endPoint.y());

	m_lastPoint = endPoint;
}


void ScribbleArea::onClearButtonClicked()
{
	m_scene->clear();
	m_drawing.clear();
	m_info.clear();
	m_currentLine = nullptr; 
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
	// checking to see how well the image is reproduced 
	QDialog* drawingDialog = new QDialog(this);
	drawingDialog->setWindowTitle("Drawing Viewer");
	drawingDialog->setAttribute(Qt::WA_StaticContents);

	QLabel* label = new QLabel(drawingDialog);
	label->setGeometry(0, 0, this->width(), this->height());

	QPixmap canvas(this->size());
	canvas.fill(Qt::white);
	QPainter painter(&canvas);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	for (size_t i = 0; i < m_drawing.size(); i++)
	{
		QColor color(QString::fromUtf8(m_info[i].first.c_str()));
		painter.setPen(QPen(color, m_info[i].second, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		int x = m_drawing[i].first;
		int y = m_drawing[i].second;

		painter.drawPoint(x, y);
	}

	label->setPixmap(canvas);
	label->setAlignment(Qt::AlignCenter);

	QVBoxLayout* layout = new QVBoxLayout(drawingDialog);
	layout->addWidget(label);

	drawingDialog->setLayout(layout);
	drawingDialog->exec();
}
