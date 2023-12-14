#pragma once
#include <QWidget>
#include <qlabel.h>
#include <QFile>
#include <QVBoxLayout>
#include "TimerWidget.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <cpr/cpr.h>
#include <crow.h>

class WordWidget : public QWidget
{
public:
	WordWidget(QWidget* parent = nullptr);
	~WordWidget();

	std::pair<size_t, QChar> GetRandomLetter(const QString& word);
	QString FormWord(const QString& word);
	void DisplayWord(TimerWidget* timer);
	void Display(const std::string& word);
	std::string FetchWordFromServer();
	void UpdateWord(const std::string& word);


private:
	QLabel* m_word;
	QString m_displayedWord;
};
