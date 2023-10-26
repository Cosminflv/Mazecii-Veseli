#pragma once
#include <iostream>

enum class PlayerRole: uint16_t
{
	Guesser,
	Painter
};

std::ostream& operator<< (std::ostream& os, PlayerRole role);
