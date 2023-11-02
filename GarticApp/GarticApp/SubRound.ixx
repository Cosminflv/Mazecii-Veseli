module;
import <iostream>;
export module Round;
export import playerRole;
export import player;

namespace garticApp
{
	export class mSubRound {
	public:
		mSubRound(mPlayer* player, std::string word);
		void SeeWord(std::string word);
		bool GuessWord(std::string word);
		void StartRound();
		int GetSecond();
		void CalculateScore(mPlayer* player, std::string word);
	private:
		mPlayer* m_player;
		std::string m_word;
		int m_duration;
		std::chrono::time_point<std::chrono::steady_clock> m_startTime;
	};
}