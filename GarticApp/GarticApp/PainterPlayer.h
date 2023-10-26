#pragma once
#include "Player.h"
class PainterPlayer : public Player
{
public:
	PainterPlayer(const std::string& username, PlayerRole role, int16_t score);
	PlayerRole GetRole() override;
};

