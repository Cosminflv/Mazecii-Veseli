#include "TimerWidget.h"
#include <QVBoxLayout>

TimerWidget::TimerWidget()
{
	m_timer = new QTimer(this);
	m_timer->setInterval(1000);
	connect(m_timer, &QTimer::timeout, this, &TimerWidget::updateTimer);

	m_timeLabel = new QLabel("01:00", this);

	m_timeLabel->setFont(QFont("Arial", 20));
	m_timeLabel->setAlignment(Qt::AlignTop);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(m_timeLabel);
	setLayout(layout);

	m_seconds = 60;

	m_timer->start();

}

QLabel* TimerWidget::GetTimeLabel() const
{
	return m_timeLabel;
}

void TimerWidget::updateTimer() 
{
	if (m_seconds > 0)
	{
		m_seconds -= 1;
		int minutes = m_seconds / 60;
		int seconds = m_seconds % 60;

		QString timeString = QString("%1:%2")
			.arg(minutes, 2, 10, QChar('0'))
			.arg(seconds, 2, 10, QChar('0'));

		m_timeLabel->setText(timeString);

		QPalette textColor = m_timeLabel->palette();

		if (m_seconds <= 60 && m_seconds > 10)
		{
			textColor.setColor(QPalette::WindowText, Qt::darkGreen);
		}
		else
		{
			textColor.setColor(QPalette::WindowText, Qt::red);
		}

		emit timerUpdate(timeString, textColor);
	}
	else
	{
		m_timer->stop();
		m_timeLabel->setText("00:00");
	}
}
