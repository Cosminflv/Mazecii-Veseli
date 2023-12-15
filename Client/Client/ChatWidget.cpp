#include "ChatWidget.h"
//#include"crow.h"
//#include<cpr/cpr.h>

ChatWidget::ChatWidget(QWidget* parent)
{
	setupUI();
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
	QString user = QString::fromUtf8(m_username.c_str());

	if (!message.isEmpty()) {
		messageDisplay->append(user + ": " + message);
		messageInput->clear();
	}

	/*crow::json::wvalue jsonChat;
	jsonChat["username"] = m_username;
	jsonChat["message"] = message.toUtf8().constData();
	std::string jsonString = jsonChat.dump();
	cpr::Response r = cpr::Post(cpr::Url("http://localhost:18080/receive_message"), cpr::Body{ jsonString });
	if (r.status_code = 200)
	{
		qDebug() << "message sent.";
	}
	else
	{
		qDebug() << "message send FAIL.";
	}*/
}

void ChatWidget::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		sendMessage();
	}
}