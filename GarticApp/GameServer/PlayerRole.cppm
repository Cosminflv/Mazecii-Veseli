module;
import <iostream>;
export module PlayerRole;

namespace garticApp
{
	export enum class PlayerRole
	{
		Guesser,
		Painter
	};

	export std::ostream& operator<< (std::ostream& os, PlayerRole role);
	export PlayerRole mConvertToRole(const std::string& role);
}