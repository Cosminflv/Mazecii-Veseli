#include "ScribbleArea.h"
#include <QtWidgets>
#include <QJsonDocument>
#include <QJsonObject>
#include <future>

ScribbleArea::ScribbleArea(QWidget* parent)
	: m_isScribbling(false), m_colorCode("#000000"), m_penWidth(6),
	m_penColor(QString::fromUtf8(m_colorCode.c_str()))
{
	setAttribute(Qt::WA_StaticContents);
}

void ScribbleArea::SetUpUi()
{
	if (m_you.GetPlayerRole() == "Painter")
	{
		int offset = 50;
		int up = 0;
		m_clearButton = new QPushButton("Clear Screen", this);
		m_clearButton->setGeometry(10, 10, 130, 30);
		m_clearButton->setFont(QFont("8514oem", 13));
		m_clearButton->setStyleSheet("background-color:#c6d2cc; color: #2d3932");
		connect(m_clearButton, &QPushButton::clicked, this, &ScribbleArea::onClearButtonClicked);

		m_selectColor = new QPushButton("More Colors", this);
		m_selectColor->setGeometry(420, 450, 120, 30);
		m_selectColor->setFont(QFont("8514oem", 13));
		m_selectColor->setStyleSheet("background-color:#c6d2cc; color: #2d3932");
		connect(m_selectColor, &QPushButton::clicked, this, &ScribbleArea::onColorButtonClicked);

		for (const int& size : m_sizes)
		{
			QPushButton* sizeButton = new QPushButton("\u2022", this);
			sizeButton->setFont(QFont("Arial", 23 + up));
			sizeButton->setGeometry(offset + 100, 10, 30, 30);
			sizeButton->setStyleSheet("background-color:#c6d2cc; color: #2d3932");
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
		m_getDrawing->setFont(QFont("8514oem", 13));
		connect(m_getDrawing, &QPushButton::clicked, this, &ScribbleArea::onGetDrawing);

		m_timer = new QTimer(this);		
		connect(m_timer, &QTimer::timeout, this, &ScribbleArea::SendToSever);
		m_timer->setInterval(300);
		m_timer->start();
	}
	else if (m_you.GetPlayerRole()  == "Guesser")
	{
		m_timer = new QTimer(this);		
		connect(m_timer, &QTimer::timeout, this, &ScribbleArea::UpdateDrawingUI);
		connect(m_timer, &QTimer::timeout, this, &ScribbleArea::DrawFromServer);
		m_timer->setInterval(300);
		m_timer->start();
	}
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

PlayerClient ScribbleArea::GetClient() const
{
	return m_you;
}

void ScribbleArea::UpdatePlayerRole(const std::string& role)
{
	m_you.UpdatePlayerRole(role);
}

void ScribbleArea::UpdateClient(const PlayerClient& you)
{
	m_you.SetUsername(you.GetUsername());
	m_you.SetAdminRole(you.GetAdminRole());
	m_you.UpdatePlayerRole(you.GetPlayerRole());
	m_you.UpdateScore(you.GetScore());
	m_you.UpdateStatus(you.GetStatus());
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
	if (m_you.GetPlayerRole() == "Painter")
	{
		if (x >= 0 && x < width() && y >= 0 && y < height())
		{
			m_drawing.push_back(std::make_pair(x, y));
			m_info.push_back(std::make_pair(m_colorCode, m_penWidth));
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
				obj["x"] = coordinate.first;
				obj["y"] = coordinate.second;
				coordinatesVect.push_back(obj);
			}

			jsonVectors["Coordinates"] = std::move(coordinatesVect);

			for (const auto& info : m_info)
			{
				crow::json::wvalue obj;
				obj["color"] = info.first;
				obj["width"] = info.second;
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

void ScribbleArea::UpdateDrawingUI()
{
	std::thread([this]() {		
		try {

			cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/drawing" });
			

			if (response.status_code == 200)
			{
				auto drawing = crow::json::load(response.text);
				if (drawing.has("Coordinates") && drawing.has("DrawingInfo"))
				{
					const auto& coordJSON = drawing["Coordinates"];
					const auto& infoJSON = drawing["DrawingInfo"];

					for (size_t i = 0; i < coordJSON.size(); i++)
					{
						const auto& coord = coordJSON[i];
						const auto& info = infoJSON[i];

						m_drawing.emplace_back(coord[i].i(), coord[i].i());
						m_info.emplace_back(info[i].s(), info[i].i());
					}
					
				}
			}
			else
			{
				qDebug() << "FAIL - Status code: " << response.status_code;
			}
			
		}
		catch (const std::exception& e)
		{
			qDebug() << "Drawing request exception: " << e.what();
		}
		
	}).detach();
}

void ScribbleArea::DrawFromServer()
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	const int breakLineThreshold = 50;

	for (size_t i = 1; i < m_drawing.size(); i++)
	{
		QColor color(QString::fromUtf8(m_info[i].first.c_str()));
		painter.setPen(QPen(color, m_info[i].second, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

		int x1 = m_drawing[i - 1].first;
		int y1 = m_drawing[i - 1].second;
		int x2 = m_drawing[i].first;
		int y2 = m_drawing[i].second;

		if (std::abs(x2 - x1) > breakLineThreshold || std::abs(y2 - y1) > breakLineThreshold)
		{
			painter.drawLine(x1, y1, x1, y1); // exceeds threshold => start new line
		}
		else
		{
			painter.drawLine(x1, y1, x2, y2); // continue current line
		}
	}
}

ScribbleArea::~ScribbleArea()
{
	delete m_clearButton;
}

void ScribbleArea::mousePressEvent(QMouseEvent* event)
{
	if (m_you.GetPlayerRole() == "Painter")
	{
		if (event->button() == Qt::LeftButton)
		{
			m_lastPoint = event->pos();
			m_isScribbling = true;
		}
	}
}

void ScribbleArea::mouseMoveEvent(QMouseEvent* event)
{
	if (m_you.GetPlayerRole() == "Painter")
	{
		if ((event->buttons() & Qt::LeftButton) && m_isScribbling)
		{
			DrawLineTo(event->pos());
			DrawInMatrix(event->pos().x(), event->pos().y());
		}
	}
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_you.GetPlayerRole() == "Painter")
	{
		if (event->button() == Qt::LeftButton && m_isScribbling) {
			DrawLineTo(event->pos());
			m_isScribbling = false;
		}
	}
}

void ScribbleArea::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
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
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.setPen(QPen(m_penColor, m_penWidth, Qt::SolidLine, Qt::RoundCap,
		Qt::RoundJoin));

	painter.drawLine(m_lastPoint, endPoint);
	m_modified = true;

	// draw line points into the matrix
	DrawInMatrix(m_lastPoint.x(), m_lastPoint.y());
	DrawInMatrix(endPoint.x(), endPoint.y());

	int rad = (m_penWidth / 2) + 2;
	QRect boundingRect = QRect(m_lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad);

	update(boundingRect);

	m_lastPoint = endPoint;
}

void ScribbleArea::onClearButtonClicked()
{
	m_path = QPainterPath();
	m_image.fill(qRgb(255, 255, 255));
	PrintCoordinates("0_coordinates.txt");
	m_drawing.clear();
	m_info.clear();
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

	const int breakLineThreshold = 40;

	for (size_t i = 1; i < m_drawing.size(); i++)
	{
		QColor color(QString::fromUtf8(m_info[i].first.c_str()));
		painter.setPen(QPen(color, m_info[i].second, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

		int x1 = m_drawing[i - 1].first;
		int y1 = m_drawing[i - 1].second;
		int x2 = m_drawing[i].first;
		int y2 = m_drawing[i].second;

		if (std::abs(x2 - x1) > breakLineThreshold || std::abs(y2 - y1) > breakLineThreshold)
		{
			painter.drawLine(x2, y2, x2, y2); // exceeds threshold => start new line
		}
		else
		{
			painter.drawLine(x1, y1, x2, y2); // continue current line
		}
	}

	label->setPixmap(canvas);
	label->setAlignment(Qt::AlignCenter);

	QVBoxLayout* layout = new QVBoxLayout(drawingDialog);
	layout->addWidget(label);

	drawingDialog->setLayout(layout);
	drawingDialog->exec();
}
