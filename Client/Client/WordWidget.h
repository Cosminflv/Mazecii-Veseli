#pragma once
#include <QWidget>
#include <qlabel.h>
#include <QFile>
#include <QVBoxLayout>
#include "TimerWidget.h"

class WordWidget : public QWidget
{
public:
	WordWidget(QWidget* parent = nullptr);
	~WordWidget();

	std::pair<size_t, QChar> GetRandomLetter(const QString& word);
	QString FormWord(const QString& word);
	void displayWord(const QString& path, TimerWidget* timer);
	

private:
	QLabel* m_word;
	QString m_displayedWord;
};
