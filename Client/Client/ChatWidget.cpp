#include "ChatWidget.h"
#include "ChatRequestException.h"

ChatWidget::ChatWidget(QWidget* parent)
{
	QVBoxLayout* layout = new QVBoxLayout;

	setFont(QFont("8514oem", 13));
	setFixedHeight(510);
	
	messageDisplay = new QTextEdit(this);
	messageDisplay->setReadOnly(true);
	messageDisplay->setFont(QFont("8514oem", 13));
	layout->addWidget(messageDisplay);

	messageInput = new QLineEdit(this);
	messageInput->setFixedHeight(35);
	messageInput->setFont(QFont("8514oem", 13));
	layout->addWidget(messageInput);

	setLayout(layout);	

	setStyleSheet("background-color: #ffffff");
}

ChatWidget::~ChatWidget()
{
	delete messageDisplay;
	delete messageInput;
}

void ChatWidget::SetUi()
{
	m_requestsTimer = new QTimer(this);
	m_requestsTimer->setInterval(1000);
	m_requestsTimer->start();
	connect(m_requestsTimer, &QTimer::timeout, this, &ChatWidget::fetchAndUpdateChat);
}

std::string ChatWidget::GetUsernameOfClient() const
{
	return m_username;
}

void ChatWidget::SetClientUsername(const std::string& user)
{
	m_username = user;
}

void ChatWidget::SetClient(const PlayerClient& client)
{
	m_you.SetUsername(client.GetUsername());
	m_you.SetAdminRole(client.GetAdminRole());
	m_you.UpdatePlayerRole(client.GetPlayerRole());
	m_you.UpdateScore(client.GetScore());
	m_you.UpdateStatus(client.GetStatus());
	if (m_you.GetPlayerRole() == "Guesser")
	{
		m_username = m_you.GetUsername();
	}
	else
	{
		m_username = " ";
	}
}

void ChatWidget::sendMessage()
{
	if (m_you.GetPlayerRole() == "Guesser")
	{
		QString message = messageInput->text();
		m_message = message.toUtf8().constData();
		QString user = QString::fromUtf8(m_username.c_str());

		if (!message.isEmpty()) {
			messageDisplay->setFont(QFont("8514oem", 13));
			messageDisplay->append(user + ": " + message);
			messageInput->clear();
			emit messageSent(user, message);
		}
		qDebug() << m_username << " - " << m_message << "\n";
	}
}

void ChatWidget::keyPressEvent(QKeyEvent* e)
{
	if ((e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
		&& m_you.GetPlayerRole() == "Guesser")
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

void ChatWidget::fetchAndUpdateChat() {
	std::thread([this]() {
		try {
			std::vector<std::pair<QString, QString>> messages;
			cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/chat" });

			if (response.status_code < 200 || response.status_code >= 300) {
				throw ChatRequestException("Failed to update chat");
			}

			auto messagesRvalue = crow::json::load(response.text);

			for (const auto& messageFromServer : messagesRvalue) {
				QString name = fromJsonToQString(messageFromServer["Username"].s());
				QString message = fromJsonToQString(messageFromServer["Message"].s());
				messages.push_back({ name, message });
			}
			// Update UI in the main thread using a queued connection
			QMetaObject::invokeMethod(this, [this, messages]() {
				updateUi(messages);
				}, Qt::QueuedConnection);

		}
		catch (const ChatRequestException& e) {
			// Handle the exception
			// Log, show an error message, or take appropriate action
			qDebug() << "Chat request exception: " << e.what();
		}
		}).detach();
}


void ChatWidget::updateUi(std::vector<std::pair<QString, QString>> messages)
{
	messageDisplay->clear();
	for (auto message : messages) {
		auto user = message.first;
		auto messageText = message.second;

		messageDisplay->setFont(QFont("8514oem", 13));
		messageDisplay->append(user + ": " + messageText);
	}
}

QString ChatWidget::fromJsonToQString(const crow::json::detail::r_string value)
{
	std::string stringValue = std::string(value);

	return QString::fromUtf8(stringValue.c_str(), static_cast<int>(stringValue.size()));
}
