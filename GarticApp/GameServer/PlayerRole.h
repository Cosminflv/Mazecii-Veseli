#pragma once
#include <iostream>

enum class PlayerRole {
	Guesser,
	Guessed,
	Painter
};

std::ostream& operator<< (std::ostream& os, PlayerRole role);
PlayerRole ConvertToRole(const std::string& role);
