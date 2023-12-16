#pragma once
#include <WinSock2.h>
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

protected:
	void keyPressEvent(QKeyEvent* e) override;

private:
	QTextEdit* messageDisplay;
	QLineEdit* messageInput;
	std::string m_username;
	std::string m_message;
};

