#include "WordWidget.h"
#include "ClientExceptions.h"
#include <QString>

WordWidget::WordWidget(QWidget* parent)
	:QWidget(parent)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	m_word = new QLabel(this);
	m_word->setFont(QFont("Arial Bold", 17));
	layout->addWidget(m_word);
}

WordWidget::~WordWidget()
{
	delete m_word;
}

std::pair<size_t, QChar> WordWidget::GetRandomLetter(const QString& word)
{
	srand(time(0));
	std::pair<size_t, QChar> pair = std::make_pair(rand() % word.size(), word[rand() % word.size()]);
	return pair;
}

QString WordWidget::FormWord(const QString& word)
{
	QString playerView = "";
	for (int i = 0; i < word.length(); i++)
	{
		playerView = playerView + "_";
	}
	return playerView;
}

void WordWidget::displayWord(TimerWidget* timer)
{
	//std::string wordString = fetchWordFromServer();

	//QString wordToDisplay = QString::fromUtf8(wordString.c_str(), static_cast<int>(wordString.size()));

	//m_word->setText(FormWord(wordToDisplay));
}
