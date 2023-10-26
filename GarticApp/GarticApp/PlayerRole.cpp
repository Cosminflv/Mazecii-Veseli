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
	else
	{
		os << "Unknown type";
	}
	return os;
}
