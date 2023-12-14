#include "PlayerDB.h"

PlayerDB::PlayerDB() :m_username(""), m_password("")
{
}

std::string PlayerDB::GetUsername() const
{
    return m_username;
}

void PlayerDB::SetUsername(const std::string& username)
{
    m_username = username;
}

std::string PlayerDB::GetPassword() const
{
    return m_password;
}

void PlayerDB::SetPassword(const std::string& password)
{
    m_password = password;
}
