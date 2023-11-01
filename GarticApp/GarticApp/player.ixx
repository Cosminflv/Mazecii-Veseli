module;
import <iostream>;
import <string>;
export import playerRole;
export module player;

namespace garticApp
{
	export class mPlayer
	{
	public:
		mPlayer(const std::string& username, mPlayerRole role, int16_t score);
		std::string GetUsername() const;
		int16_t GetScore() const;
		bool GetPlayerStatus() const;
		int SetScore(int points);
		void SetPlayerStatus(bool status);
		mPlayerRole GetRole() const;
		void SetPlayerRole(mPlayerRole role);
	private:
		std::string m_username;
		int16_t m_score;
		mPlayerRole m_role;
		bool m_hasPainted;
	};
	export std::ostream& operator <<(std::ostream& os, const mPlayer& player);
}
