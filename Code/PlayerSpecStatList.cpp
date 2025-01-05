//  PlayerSpecStatList.cpp
#include "PlayerSpecStatList.h"

// Namespace mods
using namespace std;


PlayerSpecStatList::PlayerSpecStatList(): StatList(), playerName(AliasHandler::ANON)
{
	// Constructor body (nothing needed here)
}

PlayerSpecStatList::PlayerSpecStatList(const std::string& playerName,
	const MatchList& matchList, const PropExt& propExt, const StringV& ignore, 
	const double& cutoff, const MatchVExt& matchVExt)
	: StatList(matchList, propExt, ignore, cutoff, matchVExt) // Delegate to parent
{
	this->playerName = playerName;
}  


std::string PlayerSpecStatList::getPlayerName() const
{
	return playerName;
}


bool PlayerSpecStatList::isPlayer(const std::string& playerNameIn) const
{
	return equalsIgnoreCase(this->playerName, playerNameIn);
}


std::string PlayerSpecStatList::getConciseStatS(int pos)
{
	// Retrieve underlying stat list 
	vector<Stat> statList = this->getStatList();

	// If position value is invalid, return dummy string
	if (pos < 0 || pos >= statList.size())
	{
		return "N/A (N/A)";
	}

	// Otherwise retrieve stat and generate formatted string
	Stat stat = statList.at(pos);
	return format("{} ({})", stat.getVariantValue(), stat.getPercentage());
}
