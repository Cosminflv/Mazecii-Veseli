#pragma once
#include <string>
class PlayerClient
{
public:
	PlayerClient();
	PlayerClient(std::string username);
	PlayerClient(std::string username, std::string adrole);
	PlayerClient(std::string username, std::string hasPainted, int16_t score, std::string playerRole, std::string adminRole);

	std::string GetUsername() const;
	std::string GetStatus() const;
	int16_t GetScore() const;
	std::string GetPlayerRole() const;
	std::string GetAdminRole() const;

	void SetUsername(const std::string& username);
	void UpdateStatus(const std::string& status);
	void UpdateScore(const int16_t& score);
	void UpdatePlayerRole(const std::string& playerRole);
	void SetAdminRole(const std::string& role);

private:
	std::string m_username;
	std::string m_hasPainted;
	int16_t m_score;
	std::string m_playerRole;
	std::string m_adminRole;
	
};

