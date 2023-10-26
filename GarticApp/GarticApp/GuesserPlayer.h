#pragma once
#include "player.h"
class GuesserPlayer : public Player
{
public:
	GuesserPlayer(const std::string& username, PlayerRole role, int16_t score);
	PlayerRole GetRole() override;
};

