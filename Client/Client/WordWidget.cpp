﻿#include "WordWidget.h"
#include "ClientExceptions.h"
#include <QString>
#include <random>

WordWidget::WordWidget(QWidget* parent)
	:QWidget(parent)
{
	setFont(QFont("8514oem", 17));
	QVBoxLayout* layout = new QVBoxLayout(this);
	m_word = new QLabel(this);
	layout->addWidget(m_word);
}

WordWidget::~WordWidget()
{
	delete m_word;
}

void WordWidget::SetDifficulty(const int& d)
{
	this->m_difficulty = d;
}

int WordWidget::GetDifficulty() const
{
	return m_difficulty;
}

std::pair<size_t, QChar> WordWidget::GetRandomLetter(const QString& word)
{
	// recommendation : use a std::random_device with std::mt19937, std::uniform_int_distribution
	/*srand(time(0));
	std::pair<size_t, QChar> pair = std::make_pair(rand() % word.size(), word[rand() % word.size()]);
	return pair;*/

	std::mt19937 gen(time(0));
	std::uniform_int_distribution<size_t> dist(0, word.size() - 1);
	return std::make_pair(dist(gen), word[dist(gen)]);
}

QString WordWidget::HiddenWord(const QString& word)
{
	QString hiddenWord = "";
	for (int i = 0; i < word.length(); i++)
	{
		hiddenWord = hiddenWord + "_ ";
	}
	return hiddenWord;
}


QString WordWidget::FetchWordFromServer(int difficulty)
{
	m_difficulty = difficulty;
	std::string url = "http://localhost:18080/word/" + std::to_string(m_difficulty);
	cpr::Response response = cpr::Get(cpr::Url{ url });

	if (response.error) {
		throw(WordRequestException("Word request has failed"));
	}

	QJsonDocument jsonResponse = QJsonDocument::fromJson(response.text.c_str());

	if (!jsonResponse.isObject()) {
		qDebug() << "Invalid JSON format.";
		return "";
	}

	QJsonObject jsonObject = jsonResponse.object();
	QString word = jsonObject.value("word").toString();

	qDebug() << "Word:" << word;
	return word;
}

void WordWidget::UpdateWord(const QString& word)
{
	m_word->setText(word);
}
