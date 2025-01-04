// FighterList.cpp
#include "FighterList.h"
#include <algorithm>

// Namespace mods
using namespace std;


FighterList::FighterList() : fightersV(vector<Fighter>())
{
}


FighterList::FighterList(const string& rawPairS, const string& replayType)
{
	// Remove extension
	string pairCopyS = rawPairS;
	replaceAll(pairCopyS, ".ssfrec", "");

	// Split into individual pairs
	// e.g."davo1776 (Wario)", "HexxaWyn (Naruto)" etc.
	StringV pairs = split(pairCopyS, " vs ");

	// # Check number of fighters
	int minFighters = 2;

	// Reduce minimum fighter requirement for 'Break the Target' replays
	if (contains(replayType, "BTT"))
	{
		minFighters--;
	}

	// Check amount and notify if needed
	int pLen = int(pairs.size());
	if (!(pLen >= minFighters && pLen <= 4))
	{
		warn("Unusual number of fighters detected", to_string(pLen));
	}

	// Convert every pair string to a fighter and add to list
	std::transform(pairs.begin(), pairs.end(), std::back_inserter(fightersV), 
		[](const std::string& pair) {
			return Fighter(pair);
		});
}


StringV FighterList::getPlayers()
{
	StringV players;

	std::transform(fightersV.begin(), fightersV.end(), std::back_inserter(players),
		[](const Fighter& fighter) {
			return fighter.getPlayer();
		});

	return players;
}


StringV FighterList::getChars()
{
	StringV characters;

	std::transform(fightersV.begin(), fightersV.end(), std::back_inserter(characters),
		[](const Fighter& fighter) {
			return fighter.getChar();
		});

	return characters;
}

std::string FighterList::getChar(const std::string& stdPlayerName)
{
	// For every fighter
	for (Fighter curF : fightersV)
	{
		// If player name matches given player name
		if (equalsIgnoreCase(curF.getPlayer(), stdPlayerName))
		{
			// Return that player's character
			return curF.getChar();
		}
	}

	warn("A getChar() search failed", "stdPlayerName: " + stdPlayerName);
	return "INVALID";
}


string FighterList::toString()
{
	// Holder
	string result = "";

	// Get number of fighters
	int pLen = int(fightersV.size());

	// Counter;
	int count = 0;

	// For every fighter
	for (Fighter curF : fightersV)
	{
		// Add string version
		result += curF.toString();

		// Add to counter
		count++;

		// Add separator, except on last fighter
		if (count != pLen)
		{
			result += ", ";
		}
	}

	// Return result
	return result;
}