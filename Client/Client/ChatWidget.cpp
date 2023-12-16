#include "ChatWidget.h"

ChatWidget::ChatWidget(QWidget* parent)
{
	QVBoxLayout* layout = new QVBoxLayout;

	messageDisplay = new QTextEdit(this);
	messageDisplay->setReadOnly(true);
	layout->addWidget(messageDisplay);

	messageInput = new QLineEdit(this);
	messageInput->setFixedHeight(35);
	layout->addWidget(messageInput);

	setLayout(layout);
	messageInput->setFont(QFont("Arial", 13));

	m_requestsTimer = new QTimer(this);
	m_requestsTimer->setInterval(1000); // Set interval to 1 second
	m_requestsTimer->start();
	connect(m_requestsTimer, &QTimer::timeout, this, &ChatWidget::fetchAndUpdateChat);
}

ChatWidget::~ChatWidget()
{
	delete messageDisplay;
	delete messageInput;
}

std::string ChatWidget::GetUsernameOfClient() const
{
	return m_username;
}

void ChatWidget::SetClientUsername(const std::string& user)
{
	this->m_username = user;
}

void ChatWidget::sendMessage()
{
	QString message = messageInput->text();
	m_message = message.toUtf8().constData();
	QString user = QString::fromUtf8(m_username.c_str());

	if (!message.isEmpty()) {
		messageDisplay->setFont(QFont("Arial", 13));
		messageDisplay->append(user + ": " + message);
		messageInput->clear();
	}
	qDebug() << m_username << " " << m_message << "\n";
}

void ChatWidget::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		sendMessage();
		crow::json::wvalue jsonChat;
		jsonChat["username"] = m_username;
		jsonChat["message"] = m_message;
		std::string jsonString = jsonChat.dump();
		cpr::Response r = cpr::Post(cpr::Url("http://localhost:18080/receive_message"), cpr::Body{ jsonString });
		if (r.status_code == 200)
		{
			qDebug() << "message sent.";
		}
		else
		{
			qDebug() << "message send FAIL.";
		}
	}
}

void ChatWidget::fetchAndUpdateChat()
{
	std::thread([this]() {
		std::vector<std::pair<QString, QString>> messages;
		cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/chat" });
		auto messagesRvalue = crow::json::load(response.text);

		for (const auto& messageFromServer : messagesRvalue) {
			//QString name = "Cosmin";
			//QString message = "Heello";
			QString name = fromJsonToQString(messageFromServer["Username"].s());
			QString message = fromJsonToQString(messageFromServer["Message"].s());

			messages.push_back({ name, message });
		}

		// Update UI in the main thread using a queued connection
		QMetaObject::invokeMethod(this, [this, messages]() {
			updateUi(messages);
			}, Qt::QueuedConnection);
		}).detach();
}

void ChatWidget::updateUi(std::vector<std::pair<QString, QString>> messages)
{
	messageDisplay->clear();
	for (auto message : messages) {
		auto user = message.first;
		auto messageText = message.second;

		messageDisplay->setFont(QFont("Arial", 13));
		messageDisplay->append(user + ": " + messageText);
	}
}

QString ChatWidget::fromJsonToQString(const crow::json::detail::r_string value)
{
	std::string stringValue = std::string(value);

	return QString::fromUtf8(stringValue.c_str(), static_cast<int>(stringValue.size()));
}
