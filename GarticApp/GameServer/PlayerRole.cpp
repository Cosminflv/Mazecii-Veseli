#include "PlayerRole.h"
#include <iostream>

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
		return PlayerRole::Guesser;

	if (role == "Guessed")
		return PlayerRole::Guessed;

	if (role == "Painter")
		return PlayerRole::Painter;
}
