#include "Player.h"

Player::Player(const std::string& username, PlayerRole role, int16_t score)
	: m_username(username), m_role(role), m_score(score), m_hasPainted(false)
{ }

std::string Player::GetUsername() const
{
	return m_username;
}

PlayerRole Player::GetRole()
{
	return PlayerRole();
}

void Player::SetPlayerRole(PlayerRole role)
{
	this->m_role = role;
}

int Player::SetScore(int points)
{
	m_score += points;
	return m_score;
}

int16_t Player::GetScore() const
{
	return m_score;
}

bool Player::GetPlayerStatus() const
{
	return m_hasPainted;
}

void Player::SetPlayerStatus(bool status)
{
	m_hasPainted = status;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os << player.m_username << " " << player.m_role <<
		" " << player.m_score << " " << player.m_hasPainted << std::endl;
}
