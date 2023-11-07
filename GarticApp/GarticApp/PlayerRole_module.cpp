module playerRole;
using garticApp::mPlayerRole;

std::ostream& garticApp:: operator<<(std::ostream& os, mPlayerRole role)
{
	if (role == mPlayerRole::Guesser)
	{
		os << "Guesser";
	}
	if (role == mPlayerRole::Painter)
	{
		os << "Painter";
	}
	return os;
}

mPlayerRole garticApp::mConvertToRole(const std::string& role)
{
	return role == "Guesser" ? mPlayerRole::Guesser : mPlayerRole::Painter;
}