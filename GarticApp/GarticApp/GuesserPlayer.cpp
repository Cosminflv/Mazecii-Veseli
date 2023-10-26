#include "GuesserPlayer.h"

GuesserPlayer::GuesserPlayer(const std::string& username, PlayerRole role, int16_t score)
	:Player(username,PlayerRole::Guesser, score)
{ }

PlayerRole GuesserPlayer::GetRole()
{
	return PlayerRole::Guesser;
}
