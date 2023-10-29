#pragma once
#include "PlayerRole.h"
#include <string>
#include <iostream>

class Player
{
public:
	Player(const std::string& username, PlayerRole role, int16_t score);
	std::string GetUsername() const;
	virtual PlayerRole GetRole() = 0;
	int SetScore(int points);
	friend std::ostream& operator <<(std::ostream& os, const Player& player);

private:
	std::string m_username;
	PlayerRole m_role;
	int16_t m_score;
};

