#include "PlayerClient.h"

PlayerClient::PlayerClient()
{
	// Empty
}

PlayerClient::PlayerClient(std::string username) : m_username{ username }
{
	// Empty
}

PlayerClient::PlayerClient(std::string username, std::string adrole)
	: m_username(username), m_adminRole(adrole)
{ 
	// Empty
}

PlayerClient::PlayerClient(std::string username, std::string hasPainted, int16_t score, std::string playerRole, std::string adminRole)
	: m_username{ username }, m_hasPainted{ hasPainted },
	m_score{ score }, m_playerRole{ playerRole }, m_adminRole{ adminRole }
{
	// Empty
}

std::string PlayerClient::GetUsername() const
{
	return m_username;
}

std::string PlayerClient::GetStatus() const
{
	return m_hasPainted;
}

int16_t PlayerClient::GetScore() const
{
	return m_score;
}

std::string PlayerClient::GetPlayerRole() const
{
	return m_playerRole;
}

std::string PlayerClient::GetAdminRole() const
{
	return m_adminRole;
}

void PlayerClient::SetUsername(const std::string& username)
{
	this->m_username = username;
}

void PlayerClient::UpdateStatus(const std::string& status)
{
	this->m_hasPainted = status;
}

void PlayerClient::UpdateScore(const int16_t& score)
{
	this->m_score = score;
}

void PlayerClient::UpdatePlayerRole(const std::string& playerRole)
{
	this->m_playerRole = playerRole;
}

void PlayerClient::SetAdminRole(const std::string & role)
{
	this->m_adminRole = role;
}
