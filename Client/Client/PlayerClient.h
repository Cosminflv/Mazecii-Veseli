#pragma once
#include <string>
class PlayerClient
{
public:
	PlayerClient(std::string username);
	PlayerClient(std::string username, std::string adrole);

	std::string GetUsername() const;
	std::string GetAdminRole() const;
	void SetAdminRole(const std::string& role);

private:
	std::string m_username;
	int16_t m_score;
	std::string m_playerRole;
	std::string m_adminRole;
	bool m_hasPainted;
};

