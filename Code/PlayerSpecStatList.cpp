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