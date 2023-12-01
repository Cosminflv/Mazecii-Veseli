#include "WordWidget.h"
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
		playerView = playerView + "_ ";
	}
	return playerView;
}

void WordWidget::displayWord(TimerWidget* timer)
{
	std::string wordString = fetchWordFromServer();

	if (wordString == "not found") {
		m_word->setText(FormWord("Word not loaded"));
		return;
	}
	QString wordToDisplay = QString::fromUtf8(wordString.c_str(), static_cast<int>(wordString.size()));

	m_word->setText(wordToDisplay);
}

std::string WordWidget::fetchWordFromServer()
{
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/word" });

	// Verifică dacă cererea a fost cu succes
	if (response.error) {
		// Handle error
		std::cerr << "Error: " << response.error.message << std::endl;
		return "not loaded"; //TODO : MAKE EXCEPTIONS
	}
	else {
		// Parsează răspunsul JSON
		auto jsonResponse = crow::json::load(response.text);

		// Verifică dacă parsarea a fost cu succes
		if (jsonResponse) {
			std::string wordValue = jsonResponse["word"].s();

			// Utilizează cuvântul în cadrul aplicației (afișare, stocare, etc.)
			std::cout << "Random Word: " << wordValue << std::endl;
			return wordValue;
		}
		else {
			// Handle JSON parsing error
			std::cerr << "Error parsing JSON response" << std::endl;
			return "not loaded"; //TODO : MAKE EXCEPTIONS
		}
	}
}
