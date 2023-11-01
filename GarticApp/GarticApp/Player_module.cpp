module player;
using garticApp::mPlayer;
using garticApp::mPlayerRole;

mPlayer::mPlayer(const std::string& username, mPlayerRole role, int16_t score)
	:m_username(username), m_role(role), m_score(score), m_hasPainted(false)
{ }

std::string mPlayer::GetUsername() const
{
	return m_username;
}

int16_t mPlayer::GetScore() const
{
	return m_score;
}

bool mPlayer::GetPlayerStatus() const
{
	return m_hasPainted;
}

mPlayerRole mPlayer::GetRole() const
{
	return m_role;
}

int mPlayer::SetScore(int points)
{
	m_score += points;
	return m_score;
}

void mPlayer::SetPlayerStatus(bool status)
{
	m_hasPainted = status;
}

void mPlayer::SetPlayerRole(mPlayerRole role)
{
	this->m_role = role;
}

std::ostream& garticApp::operator<<(std::ostream& os, const mPlayer& player)
{
	return os << player.GetUsername() << " ";
}