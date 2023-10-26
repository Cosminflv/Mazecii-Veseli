#include "PlayerRole.h"

std::ostream& operator<<(std::ostream& os, PlayerRole role)
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

PlayerRole ConvertToRole(const std::string& role)
{
	if (role == "Guesser")
	{
		return PlayerRole::Guesser;
	}
	if (role == "Painter")
	{
		return PlayerRole::Painter;
	}
	throw std::exception("Unknown player type.\n");
}
