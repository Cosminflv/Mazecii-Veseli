module; 
import <iostream>;
import <ctime>;
import <cstdlib>;
import <chrono>;
import <thread>;
import <string>;
export module SubRound;
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
		void ChoosePainter(std::vector<mPlayer*>& players);
		void CalculateScore(mPlayer* player, std::string word);
		bool HaveAllPlayersGuessed();
		bool HasSubRoundEnded();
		int GetSizeOfPlayers();
	private:
		std::vector<mPlayer*> m_player;
		int m_counterGuessingPlayers;
		std::string m_word;
		int m_duration;
		bool m_hasTimeEnded;
		std::chrono::time_point<std::chrono::steady_clock> m_startTime;
	};
}