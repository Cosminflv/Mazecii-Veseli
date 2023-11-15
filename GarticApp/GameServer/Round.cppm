module;
import <iostream>;
export import Player;
export import SubRound;
export module Round;
import<vector>;

namespace garticApp
{
	export class mRound
	{
	public:
		mRound(std::vector<SubRound*>subRounds);
		int GetSizeOfRound();
		void ResetStatus();
		bool RoundIsOver();

	private:
		std::vector<SubRound*>m_subRounds;
		std::vector<Player*>m_players;
	};
}