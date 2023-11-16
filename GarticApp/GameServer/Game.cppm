module;
import <iostream>;
import<map>;
import<set>;
import<vector>;
export import Player;
export import Round;
export module Game;

namespace garticApp
{
	export class Game
	{
	public:
		Game(std::vector<Player*>players, std::map<Player*, int>leaderboard, std::vector<Round*>rounds);
		Game();
		std::vector<Player*> GetPlayers() const;
		std::vector<Round*>GetRounds()const;
		bool CheckUniquePlayerUsername(Player* player);
		void AddPlayer(Player* player);
		//no need to add rounds during a game,
		//the number of rounds is given by the number of players
		void AddRound(Round* round);
		std::map<Player*, int>GetLeaderboard()const;
		void PlayRound();
		void StartGame();
		void EndGame();
		void ResetGame();
		void UpdateLeaderboard();
		~Game();

	private:
		std::vector<Player*>m_players;
		std::map<Player*, int>m_leaderboard;
		std::vector<Round*>m_rounds;

	};
}
