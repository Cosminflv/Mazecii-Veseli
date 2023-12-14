#pragma once
#include<string>
class PlayerDB
{
public:
	PlayerDB();
	std::string GetUsername() const;
	void SetUsername(const std::string& username);
	std::string GetPassword()const;
	void SetPassword(const std::string& password);


private:
	std::string m_username;
	std::string m_password;
};

