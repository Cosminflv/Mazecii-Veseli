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
	// recommendation : use a std::random_device with std::mt19937, std::uniform_int_distribution
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

//void WordWidget::DisplayWord(TimerWidget* timer)
//{
//	std::string wordString = FetchWordFromServer();
//
//	QString wordToDisplay = QString::fromUtf8(wordString.c_str(), static_cast<int>(wordString.size()));
//
//	m_word->setText(FormWord(wordToDisplay));
//}

void WordWidget::Display(const std::string& word)
{
	QString str = QString::fromUtf8(word.c_str());
	m_word->setText(str);
}

QString WordWidget::fetchWordFromServer(int difficulty)
{
	std::string url = "http://localhost:18080/word/" + std::to_string(difficulty);
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
