#include "TimerWidget.h"

#include <QVBoxLayout>

TimerWidget::TimerWidget()
{
	m_timer = new QTimer(this);
	m_timer->setInterval(1000);
	connect(m_timer, &QTimer::timeout, this, &TimerWidget::updateTimer);

	timeLabel = new QLabel("00:00", this);

	timeLabel->setFont(QFont("Arial", 10));
	timeLabel->setAlignment(Qt::AlignTop);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(timeLabel);
	setLayout(layout);

	m_seconds = 0;

	m_timer->start();
}

void TimerWidget::updateTimer() {
	m_seconds += 1;
	if (m_seconds <= 60) {
		int minutes = m_seconds / 60;
		int seconds = m_seconds % 60;

		QString timeString = QString("%1:%2")
			.arg(minutes, 2, 10, QChar('0'))
			.arg(seconds, 2, 10, QChar('0'));

		timeLabel->setText(timeString);
	}
	else {
		m_timer->stop();
		timeLabel->setText("01:00");
	}
}
