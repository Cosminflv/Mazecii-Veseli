#include "ChatWidget.h"
#include"crow.h"
#include<cpr/cpr.h>

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