module;
import <iostream>;
import <random>;
import <chrono>;
import <thread>;
import <string>;
export module SubRound;
export import PlayerRole;
export import Player;
namespace garticApp
{
	export class SubRound {
	public:
		SubRound(Player* player, const std::string& word);
		void SeeWord(const std::string& word);
		bool GuessWord(const std::string& word);
		void StartRound();
		int GetSecond();
		void ChoosePainter(std::vector<Player*>& players);
		void CalculateScore(Player* player, const std::string& word);
		bool HaveAllPlayersGuessed();
		bool HasSubRoundEnded();
		int GetSizeOfPlayers();
	private:
		std::vector<Player*> m_player;
		int m_counterGuessingPlayers;
		std::string m_word;
		int m_duration;
		bool m_hasTimeEnded;
		std::chrono::time_point<std::chrono::steady_clock> m_startTime;
	};
}