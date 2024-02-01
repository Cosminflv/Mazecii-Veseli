#pragma once
#include "PlayerRole.h"
#include "AdminRole.h"

class Player
{
public:

	Player() = default;
	Player(const std::string& username, PlayerRole role, int16_t score);
	Player(const std::string& username);
	Player(const std::string& username, AdminRole arole, PlayerRole role);

	std::string GetUsername() const;
	void SetUsername(const std::string& username);

	void SetSecond(int second);
	int GetSecond() const;
	void SetScore(int16_t points);
	void CalculateGuesserScore(std::chrono::seconds second);
	int16_t GetScore() const;
	void AlreadyGuessed(bool ok);
	bool HasNotGuessedYet();

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

	bool operator==(const Player& other) const;

private:
	std::string m_username;
	int16_t m_score;
	int m_second;
	PlayerRole m_playerRole;
	AdminRole m_adminRole;
	bool m_hasPainted;
	bool m_alreadyGuessed;
};

std::ostream& operator <<(std::ostream& os, const Player& player);