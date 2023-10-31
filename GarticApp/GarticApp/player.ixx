module;
import <iostream>;
export module player;

namespace garticApp
{
	export class Player
	{
	public:
		enum class PlayerRole : uint8_t
		{
			Guesser,
			Painter
		};

		friend std::ostream& operator << (std::ostream& os, const PlayerRole& role);
		PlayerRole ConvertToRole(const std::string& role);
		Player(const std::string& username, PlayerRole role, int16_t score);
		std::string GetUsername() const;
		virtual PlayerRole GetRole() = 0;
		int SetScore(int points);
		int16_t  GetScore();
		friend std::ostream& operator <<(std::ostream& os, const Player& player);

	private:
		std::string m_username;
		PlayerRole m_role;
		int16_t m_score;
	};
}
