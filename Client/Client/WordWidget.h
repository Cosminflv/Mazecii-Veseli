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
#include <QRandomGenerator>

class WordWidget : public QWidget
{
public:
	WordWidget(QWidget* parent = nullptr);
	~WordWidget();

	void SetDifficulty(const uint16_t& d);
	uint16_t GetDifficulty() const;
	QLabel* GetWordLabel() const;
	//QString FetchWordFromServer(uint16_t difficulty);
	QString FetchSeenWordFromServer(uint16_t difficulty);
	QString FetchHiddenWordFromServer(uint16_t difficulty);
	void FetchTheWord(uint16_t difficulty);
	QString FetchUpdatedWordFromServer();
	void UpdateWord(const QString& word);

public slots:
	void UpdateWordFromServer(); //pt interfata grafica

private:
	QLabel* m_word;
	uint16_t m_difficulty;
};
