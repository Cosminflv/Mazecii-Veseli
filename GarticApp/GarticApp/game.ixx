module;
import <iostream>;
import<map>;
import<set>;
import<vector>;
export import player;
export import round;
export module game;

namespace garticApp
{
	export class mGame
	{
	public:
		mGame(std::vector<mPlayer*>players, std::map<mPlayer*, int>leaderboard, std::vector<mRound*>rounds);
		mGame();
		std::vector<mPlayer*> GetPlayers() const;
		std::vector<mRound*>GetRounds()const;
		bool CheckUniquePlayerUsername(mPlayer* player);
		void AddPlayer(mPlayer* player);
		//no need to add rounds during a game,
		//the number of rounds is given by the number of players
		void AddRound(mRound* round);
		std::map<mPlayer*, int>GetLeaderboard()const;
		void PlayRound();
		void StartGame();
		void EndGame();
		void ResetGame();
		void UpdateLeaderboard();
		~mGame();

	private:
		std::vector<mPlayer*>m_players;
		std::map<mPlayer*, int>m_leaderboard;
		std::vector<mRound*>m_rounds;

	};
}
