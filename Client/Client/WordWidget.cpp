#include "WordWidget.h"
#include "ClientExceptions.h"
#include <QString>
#include <random>

WordWidget::WordWidget(QWidget* parent)
	:QWidget(parent)
{
	setFont(QFont("Rockwell", 20));
	QVBoxLayout* layout = new QVBoxLayout(this);
	m_word = new QLabel(this);
	layout->addWidget(m_word);
}

WordWidget::~WordWidget()
{
	delete m_word;
}

void WordWidget::SetDifficulty(const uint16_t& d)
{
	this->m_difficulty = d;
}

uint16_t WordWidget::GetDifficulty() const
{
	return m_difficulty;
}

QLabel* WordWidget::GetWordLabel() const
{
	return m_word;
}

//a se utiliza pentru preluarea cuvantului vazut
QString WordWidget::FetchSeenWordFromServer(uint16_t difficulty)
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
    QString visibleWord = jsonObject.value("visibleWord").toString();

    qDebug() << "Visible Word:" << visibleWord;

    // Întoarce cuvântul afișat
    return visibleWord;
}

//a se utiliza pentru preluarea cuvantului ascuns
QString WordWidget::FetchHiddenWordFromServer(uint16_t difficulty)
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
    QString hiddenWord = jsonObject.value("hiddenWord").toString();

    qDebug() << "Hidden Word:" << hiddenWord;

    // Întoarce cuvântul ascuns
    return hiddenWord;
}


void WordWidget::FetchTheWord(uint16_t difficulty)
{
    std::string url = "http://localhost:18080/word/" + std::to_string(difficulty);
    cpr::Response firstResponse = cpr::Get(cpr::Url{url});
}

QString WordWidget::FetchUpdatedWordFromServer()
{
    std::string url = "http://localhost:18080/updateWord/";
    cpr::Response response = cpr::Get(cpr::Url{ url });

    if (response.error) {
        throw(WordRequestException("Word request has failed"));
    }
    return response.text.c_str();
}

void WordWidget::UpdateWordFromServer()
{
    try {
        QString updatedWord = FetchUpdatedWordFromServer();
        UpdateWord(updatedWord);
    }
    catch (const WordRequestException& ex) {
        qDebug() << "Error updating word from server ";
    }
}


void WordWidget::UpdateWord(const QString& word)
{
	m_word->setText(word);
}
