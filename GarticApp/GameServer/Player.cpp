#include "Player.h"
#include <iostream>

Player::Player(const std::string& username, PlayerRole role, int16_t score)
	:m_username{ username }, m_role{ role }, m_score{ score }, m_hasPainted{ false }
{ }

std::string Player::GetUsername() const
{
	return m_username;
}

int16_t Player::GetScore() const
{
	return m_score;
}

bool Player::GetPlayerStatus() const
{
	return m_hasPainted;
}

PlayerRole Player::GetRole() const
{
	return m_role;
}

std::string Player::GetRoleAsString() const
{
	return (m_role == PlayerRole::Guesser) ? "Guesser" : "Painter";
}

int Player::SetScore(const int &points)
{
	m_score += points;
	return m_score;
}

void Player::SetPlayerStatus(const bool &status)
{
	m_hasPainted = status;
}

void Player::SetPlayerRole(const PlayerRole &role)
{
	this->m_role = role;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os << "Username: "<<player.GetUsername() << "\nRole: " << player.GetRole() << "\nScore: " <<
		player.GetScore() << "\nStatus: " << player.GetPlayerStatus() << "\n";
}