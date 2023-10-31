module playerRole;
using garticApp::PlayerRole;

std::ostream& garticApp:: operator<<(std::ostream& os, PlayerRole role)
{
	if (role == PlayerRole::Guesser)
	{
		os << "Guesser";
	}
	if (role == PlayerRole::Painter)
	{
		os << "Painter";
	}
	return os;
}

PlayerRole garticApp::ConvertToRole(const std::string& role)
{
	return role == "Guesser" ? PlayerRole::Guesser : PlayerRole::Painter;
}