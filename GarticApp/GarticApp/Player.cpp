#include "Player.h"

Player::Player(const std::string& username, PlayerRole role, int16_t score)
	: m_username(username), m_role(role), m_score(score)
{ }

std::string Player::GetUsername() const
{
	return m_username;
}

PlayerRole Player::GetRole()
{
	return PlayerRole();
}

int Player::SetScore(int points)
{
	m_score += points;
	return m_score;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os << player.m_username << " " << player.m_role <<
		" " << player.m_score << std::endl;
}
