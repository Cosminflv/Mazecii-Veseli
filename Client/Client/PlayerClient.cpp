#include "PlayerClient.h"

PlayerClient::PlayerClient(std::string username) : m_username{ username }
{ }

PlayerClient::PlayerClient(std::string username, std::string adrole)
	: m_username(username), m_adminRole(adrole)
{ }

std::string PlayerClient::GetUsername() const
{
	return m_username;
}

std::string PlayerClient::GetAdminRole() const
{
	return m_adminRole;
}

void PlayerClient::SetAdminRole(const std::string & role)
{
	m_adminRole = role;
}
