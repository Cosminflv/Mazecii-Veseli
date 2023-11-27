#pragma once
#include <QtWidgets>
#include <QKeyEvent>

class ChatWidget : public QWidget
{
public:
	ChatWidget(QWidget* parent = nullptr);
	~ChatWidget();

private slots:
	void sendMessage();

private:
	void setupUI()
	{
		QVBoxLayout* layout = new QVBoxLayout;

		messageDisplay = new QTextEdit(this);
		messageDisplay->setReadOnly(true);
		layout->addWidget(messageDisplay);

		messageInput = new QLineEdit(this);
		messageInput->setFixedHeight(35);
		layout->addWidget(messageInput);

		
	//	sendButton = new QPushButton("Send", this);
	//	layout->addWidget(sendButton);

		setLayout(layout);
	}

protected:
	void keyPressEvent(QKeyEvent* e) override;

private:
	QTextEdit* messageDisplay;
	QLineEdit* messageInput;
	//QPushButton* sendButton;
};

