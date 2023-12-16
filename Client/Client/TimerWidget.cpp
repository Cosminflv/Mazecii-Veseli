#include "TimerWidget.h"
#include <QVBoxLayout>
#include"crow.h"
#include<cpr/cpr.h>



TimerWidget::TimerWidget()
{
	m_timeLabel = new QLabel("01:00", this);
	m_timeLabel->setFont(QFont("Arial", 20));
	m_timeLabel->setAlignment(Qt::AlignTop);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(m_timeLabel);
	setLayout(layout);

	// Create and configure the timer
	m_timer = new QTimer(this);
	m_timer->setInterval(1000); // Set interval to 1 second
	m_timer->start();
	connect(m_timer, &QTimer::timeout, this, &TimerWidget::fetchAndUpdateTimer);
}

QLabel* TimerWidget::GetTimeLabel() const
{
	return m_timeLabel;
}

void TimerWidget::fetchAndUpdateTimer() {
	// Fetch the timer value in a separate thread
	std::thread([this]() {
		cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/timer" });
		auto remainingTimeRvalue = crow::json::load(response.text);
		auto remainingTime = static_cast<int>(remainingTimeRvalue["Seconds"].u());

		// Update UI in the main thread using a queued connection
		QMetaObject::invokeMethod(this, [this, remainingTime]() {
			updateUi(remainingTime);
			}, Qt::QueuedConnection);
		}).detach();
}

void TimerWidget::stopTimer()
{
	m_timer->stop();
}

void TimerWidget::startTimer()
{
	m_timer->start();
}

void TimerWidget::updateUi(int remainingTime)
{
	if (remainingTime > 0) {
		int minutes = remainingTime / 60;
		int seconds = remainingTime % 60;

		QString timeString = QString("%1:%2")
			.arg(minutes, 2, 10, QChar('0'))
			.arg(seconds, 2, 10, QChar('0'));

		m_timeLabel->setText(timeString);

		QPalette textColor = m_timeLabel->palette();
		if (remainingTime <= 60 && remainingTime > 10) {
			textColor.setColor(QPalette::WindowText, Qt::darkGreen);
		}
		else {
			textColor.setColor(QPalette::WindowText, Qt::red);
		}
		m_timeLabel->setPalette(textColor);
	}
	else {
		stopTimer();
		m_timeLabel->setText("00:00");
	}
}
