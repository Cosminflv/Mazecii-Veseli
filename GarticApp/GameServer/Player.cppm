module;
import <iostream>;
import <string>;
export import PlayerRole;
export module Player;

namespace garticApp
{
	export class Player
	{
	public:
		Player(const std::string& username, PlayerRole role, int16_t score);
		std::string GetUsername() const;
		int16_t GetScore() const;
		bool GetPlayerStatus() const;
		int SetScore(int points);
		void SetPlayerStatus(bool status);
		PlayerRole GetRole() const;
		void SetPlayerRole(PlayerRole role);
	private:
		std::string m_username;
		int16_t m_score;
		PlayerRole m_role;
		bool m_hasPainted;
	};
	export std::ostream& operator <<(std::ostream& os, const Player& player);
}