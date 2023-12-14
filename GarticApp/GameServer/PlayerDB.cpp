#include "PlayerDB.h"

std::string PlayerDB::GetUsername() const
{
    return m_username;
}

void PlayerDB::SetUsername(const std::string& username)
{
    this->m_username = username;
}

std::string PlayerDB::GetPassword() const
{
    return m_password;
}

void PlayerDB::SetPassword(const std::string& password)
{
    this->m_password = password;
}
