module;
import <iostream>;
import <string>;
export import playerRole;
export module player;

namespace garticApp
{
	export class Player
	{
	public:
		Player(const std::string& username, PlayerRole role, int16_t score);
		std::string GetUsername() const;
		int16_t GetScore();
		bool GetPlayerStatus();
		int SetScore(int points);
		void SetPlayerStatus(bool status);

	private:
		std::string m_username;
		int16_t m_score;
		PlayerRole m_role;
		bool m_hasPainted;
	};
	export std::ostream& operator <<(std::ostream& os, const Player& player);
}
