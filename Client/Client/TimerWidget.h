#pragma once

#include <QWidget>
#include <qlabel.h>
#include <QTimer>

class TimerWidget : public QWidget
{
public:
	TimerWidget();

private slots:
	void updateTimer();

private:
	int m_seconds;

	QTimer* m_timer;
	QLabel* timeLabel;
};

