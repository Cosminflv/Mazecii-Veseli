#include "ChatWidget.h"

ChatWidget::ChatWidget(QWidget* parent)
{
	setupUI();
	connect(sendButton, &QPushButton::clicked, this, &ChatWidget::sendMessage);
}

ChatWidget::~ChatWidget()
{
	delete messageDisplay;
	delete messageInput;
	delete sendButton;
}

void ChatWidget::sendMessage()
{
	QString message = messageInput->text();
	if (!message.isEmpty()) {
		messageDisplay->append("You: " + message);
		messageInput->clear();
	}
}
