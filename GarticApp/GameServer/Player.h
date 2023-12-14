#pragma once
#include "PlayerRole.h"
class Player
{
public:

	Player() = default;
	Player(const std::string& username, PlayerRole role, int16_t score);

	std::string GetUsername() const;
	void SetUsername(const std::string& username);

	int16_t GetScore() const;
	void SetScore(int16_t points);

	bool GetPlayerStatus() const;
	void SetPlayerStatus(const bool &status);

	PlayerRole GetRole() const;
	std::string GetRoleAsString() const;
	void SetPlayerRole(const PlayerRole &role);

private:
	std::string m_username;
	int16_t m_score;
	PlayerRole m_role;
	bool m_hasPainted;
};

std::ostream& operator <<(std::ostream& os, const Player& player);
