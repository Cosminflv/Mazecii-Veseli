#pragma once
#include <WinSock2.h>
#include <QtWidgets>
#include <QKeyEvent>
#include <string>
#include <QTimer>
#include "PlayerClient.h"
#include"crow.h"
#include<cpr/cpr.h>

class ChatWidget : public QWidget
{
	Q_OBJECT
public:
	ChatWidget(QWidget* parent = nullptr);
	~ChatWidget();

	std::string GetUsernameOfClient() const;
	void SetClientUsername(const std::string& user);
	QString fromJsonToQString(const crow::json::detail::r_string value);

signals:
	void messageSent(const QString& username, const QString& message); //emite semnal cand un mesaj a fost trimis

private slots:
	void sendMessage();
	void fetchAndUpdateChat();
	void updateUi(std::vector<std::pair<QString, QString>> messages);

protected:
	void keyPressEvent(QKeyEvent* e) override;

private:

	QTimer* m_requestsTimer;

	QTextEdit* messageDisplay;
	QLineEdit* messageInput;
	std::string m_username;
	std::string m_message;
};

