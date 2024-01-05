#include "PlayerDB.h"

PlayerDB::PlayerDB(const std::string& username, const std::string& password)
    :m_username{username},m_password{password}
{
    // Empty
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

uint16_t PlayerDB::GetId() const
{
    return m_id;
}

void PlayerDB::SetId(uint16_t id)
{
    m_id = id;
}
