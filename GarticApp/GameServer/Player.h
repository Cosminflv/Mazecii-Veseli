#pragma once
#include "PlayerRole.h"
#include "AdminRole.h"
class Player
{
public:

	Player() = default;
	Player(const std::string& username, PlayerRole role, int16_t score);
	Player(const std::string& username);

	std::string GetUsername() const;
	void SetUsername(const std::string& username);

	int16_t GetScore() const;
	void SetScore(int16_t points);

	bool GetPlayerStatus() const;
	void SetPlayerStatus(const bool &status);

	PlayerRole GetPlayerRole() const;
	std::string GetPlayerRoleAsString() const;
	AdminRole GetAdminRole() const;
	std::string GetAdminRoleAsString() const;

	void SetPlayerRole(PlayerRole playerRole);
	void SetAdminRole(AdminRole adminRole);
	static AdminRole RoleStatusFromString(const std::string& adrole);
	void SetAdminRoleAsString(const std::string& adrole);

private:
	std::string m_username;
	int16_t m_score;
	PlayerRole m_playerRole;
	AdminRole m_adminRole;
	bool m_hasPainted;
};

std::ostream& operator <<(std::ostream& os, const Player& player);
