#pragma once
#include<string>
class PlayerDB
{
public:
	PlayerDB()=default;
	PlayerDB(const std::string& username, const std::string& password);

	std::string GetUsername() const;
	void SetUsername(const std::string& username);

	std::string GetPassword()const;
	void SetPassword(const std::string& password);


private:
	std::string m_username;
	std::string m_password;
};

