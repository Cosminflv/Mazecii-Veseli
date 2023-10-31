module player;
using garticApp::Player;
using garticApp::PlayerRole;

Player::Player(const std::string& username, PlayerRole role, int16_t score)
	:m_username(username), m_role(role), m_score(score)
{ }

std::string Player::GetUsername() const
{
	return m_username;
}

int16_t Player::GetScore()
{
	return m_score;
}

int Player::SetScore(int points)
{
	m_score += points;
	return m_score;
}

std::ostream& garticApp::operator<<(std::ostream& os, const Player& player)
{
	return os << player.GetUsername() << " ";
}