#include "PainterPlayer.h"

PainterPlayer::PainterPlayer(const std::string& username, PlayerRole role, int16_t score)
	:Player(username, PlayerRole::Painter, score)
{ }

PlayerRole PainterPlayer::GetRole()
{
	return PlayerRole::Painter;
}
