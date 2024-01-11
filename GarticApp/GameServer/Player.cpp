#include "Player.h"
#include <iostream>

Player::Player(const std::string& username, PlayerRole role, int16_t score)
	:m_username{ username }, m_playerRole{ role },
	m_score{ score }, m_hasPainted{ false }, m_adminRole{ AdminRole::NonAdmin }
{
	// Empty
}

Player::Player(const std::string& username) : m_username{ username }
{
	// Empty
}

std::string Player::GetUsername() const
{
	return m_username;
}

void Player::SetUsername(const std::string& username)
{
	m_username = username;
}

int16_t Player::GetScore() const
{
	return m_score;
}

bool Player::GetPlayerStatus() const
{
	return m_hasPainted;
}

PlayerRole Player::GetPlayerRole() const
{
	return m_playerRole;
}

AdminRole Player::GetAdminRole() const
{
	return m_adminRole;
}

std::string Player::GetAdminRoleAsString() const
{
	if (m_adminRole == AdminRole::Admin)
		return "Admin";
	if (m_adminRole == AdminRole::NonAdmin)
		return "NonAdmin";
}

std::string Player::GetPlayerRoleAsString() const
{
	if (m_playerRole == PlayerRole::Guessed)
		return "Guessed";
	if (m_playerRole == PlayerRole::Guesser)
		return "Guesser";
	if (m_playerRole == PlayerRole::Painter)
		return "Painter";
}
void Player::SetScore(int16_t points)
{
	m_score = points;
}

void Player::CalcultateGuesserScore(std::chrono::seconds second)
{
	int intSecond = second.count();
	std::cout << "\nIn metodata calculate score secunda e: " << intSecond << "\n";
	if (intSecond > 30)
	{
		SetScore(100);
	}
	else if (intSecond<30 && intSecond!=0)
	{
		int score = static_cast<int>(std::round(((60 - (30+(30-intSecond))) * 100) / 30)); 
		SetScore(score);
	}
	else if (intSecond <= 0)
	{
		std::cout << "Intra aici?";
		SetScore(-50);
	}
}

void Player::SetPlayerStatus(const bool &status)
{
	m_hasPainted = status;
}

void Player::SetPlayerRole(PlayerRole role)
{
	this->m_playerRole = role;
}

void Player::SetAdminRole(AdminRole adminRole)
{
	this->m_adminRole = adminRole;
}

AdminRole Player::RoleStatusFromString(const std::string& adrole)
{
	if (adrole == "Admin")
		return AdminRole::Admin;
	else if (adrole == "NonAdmin")
		return AdminRole::NonAdmin;
}

void Player::SetAdminRoleAsString(const std::string& adrole)
{
	m_adminRole = RoleStatusFromString(adrole);
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os << "Username: "<<player.GetUsername() << "\nRole: " << player.GetPlayerRole() << "\nScore: " <<
		player.GetScore() << "\nStatus: " << player.GetPlayerStatus() << "\n";
}