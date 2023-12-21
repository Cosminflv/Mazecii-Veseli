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

	void SetDifficulty(const uint16_t& d);
	uint16_t GetDifficulty() const;

	QString FetchWordFromServer(uint16_t difficulty);
	QString HiddenWord(const QString& word);
	void UpdateWord(const QString& word);
	std::pair<size_t, QChar> GetRandomLetter(const QString& word);

public slots:
	void revealRandomLetter();
private:
	QLabel* m_word;
	QString m_displayedWord;
	uint16_t m_difficulty;
};
