#pragma once
#include <QtWidgets>
#include <QKeyEvent>
#include <string>

class ChatWidget : public QWidget
{
public:
	ChatWidget(QWidget* parent = nullptr);
	~ChatWidget();

	std::string GetUsernameOfClient() const;
	void SetClientUsername(const std::string& user);

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

		setLayout(layout);
	}

protected:
	void keyPressEvent(QKeyEvent* e) override;

private:
	QTextEdit* messageDisplay;
	QLineEdit* messageInput;
	std::string m_username;
	std::string m_message;
};

