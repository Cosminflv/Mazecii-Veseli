module;
import <iostream>;
import <chrono>;
import <thread>;
export module SubRound;
export import playerRole;
export import player;
namespace garticApp
{
	export class mSubRound {
	public:
		mSubRound(mPlayer* player, std::string word);
		//hasSubRoundEnded - dupa ce trec 60 de sec se terminna automat sau daca toti jucatorii ghicesc inainte de 60sec se trece la urmatoarea subrunda
		//ajutator - atribut HaveAllPlayersGuessTheWord? ->  
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