#pragma once

#include <QWidget>
#include <qlabel.h>
#include <QTimer>
#include <QPalette>

class TimerWidget : public QWidget
{
	Q_OBJECT

public:
	TimerWidget();
	QLabel* GetTimeLabel() const;

signals:
	void timerUpdate(const QString& timeString, const QPalette& textColor);

private slots:
	void updateTimer();

private:
	int m_seconds;

	QTimer* m_timer;
	QLabel* m_timeLabel;
};

