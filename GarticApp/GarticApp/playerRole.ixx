module;
import <iostream>;
export module playerRole;

namespace garticApp
{
	export enum class mPlayerRole
	{
		Guesser,
		Painter
	};
	export std::ostream& operator<< (std::ostream& os, mPlayerRole role);
	export mPlayerRole ConvertToRole(const std::string& role);
}