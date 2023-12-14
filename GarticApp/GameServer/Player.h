#pragma once
#include "PlayerRole.h"
class Player
{
public:
	Player(const std::string& username, PlayerRole role, int16_t score);
	std::string GetUsername() const;
	void SetUsername(const std::string& username);
	int16_t GetScore() const;
	bool GetPlayerStatus() const;
	PlayerRole GetRole() const;
	void SetScore(const int16_t &points);
	void SetPlayerStatus(const bool &status);
	std::string GetRoleAsString() const;
	void SetPlayerRole(const PlayerRole &role);
private:
	std::string m_username;
	int16_t m_score;
	PlayerRole m_role;
	bool m_hasPainted;
};

std::ostream& operator <<(std::ostream& os, const Player& player);
