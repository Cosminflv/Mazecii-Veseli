#pragma once
#include <QtWidgets>

class ChatWidget : public QWidget
{
public:
	ChatWidget(QWidget* parent = nullptr);
	~ChatWidget();

private slots:
	void sendMessage();

private:
	void setupUI() {
		QVBoxLayout* layout = new QVBoxLayout;

		messageDisplay = new QTextEdit(this);
		messageDisplay->setReadOnly(true);
		layout->addWidget(messageDisplay);

		messageInput = new QLineEdit(this);
		layout->addWidget(messageInput);

		sendButton = new QPushButton("Send", this);
		layout->addWidget(sendButton);

		setLayout(layout);
	}
private:
	QTextEdit* messageDisplay;
	QLineEdit* messageInput;
	QPushButton* sendButton;
};

