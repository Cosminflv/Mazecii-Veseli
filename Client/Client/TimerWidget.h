#pragma once

#include <QWidget>
#include <qlabel.h>
#include <QTimer>
#include <QPalette>
#include"crow.h"
#include<cpr/cpr.h>
#include "WordWidget.h"

class TimerWidget : public QWidget
{
	Q_OBJECT

public:
	TimerWidget();
	QLabel* GetTimeLabel() const;

signals:
	void timerUpdate(const QString& timeString, const QPalette& textColor);
	void wordUpdated(const QString& updatedWord);
	void halfTimeReachedSignal();
public slots:
	void startTimer();
	void stopTimer();

private slots:
	void fetchAndUpdateTimer();
	void updateUi(int remainingTime);

private:
	bool m_halfTimeReached;
	QTimer* m_timer;
	QLabel* m_timeLabel;
	int m_revealedLettersCount;
};

