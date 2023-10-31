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
		int SetScore(int points);

	private:
		std::string m_username;
		int16_t m_score;
		PlayerRole m_role;
	};
	export std::ostream& operator <<(std::ostream& os, const Player& player);
}
