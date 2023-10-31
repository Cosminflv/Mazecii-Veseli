module;
import <iostream>;
export module playerRole;

namespace garticApp
{
	export enum class PlayerRole
	{
		Guesser,
		Painter
	};
	export std::ostream& operator<< (std::ostream& os, PlayerRole role);
	export PlayerRole ConvertToRole(const std::string& role);
}