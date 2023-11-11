module;
import <iostream>;
export import player;
export import SubRound;
export module round;
import<vector>;

namespace garticApp
{
	export class mRound
	{
	public:
		mRound(std::vector<mSubRound*>subRounds);
		int GetSizeOfRound();
		void ResetStatus();
		bool RoundIsOver();

	private:
		std::vector<mSubRound*>m_subRounds;
		std::vector<mPlayer*>m_players;

	};
}