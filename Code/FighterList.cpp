// FighterList.cpp
#include "FighterList.h"

// Namespace mods
using namespace std;


FighterList::FighterList()
{
	fightersV = vector<Fighter>();
}


FighterList::FighterList(string rawPairS, string replayType)
{
	// Remove extension
	replaceAll(rawPairS, ".ssfrec", "");

	// Split into individual pairs
	// e.g."davo1776 (Wario)", "HexxaWyn (Naruto)" etc.
	StringV pairs = split(rawPairS, " vs ");

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
	for (string curPairS : pairs) {
		fightersV.push_back(Fighter(curPairS));
	}
}


StringV FighterList::getPlayers()
{
	StringV players;
	for (Fighter curF : fightersV)
	{
		players.push_back(curF.getPlayer());
	}
	return players;
}


StringV FighterList::getChars()
{
	StringV players;
	for (Fighter curF : fightersV)
	{
		players.push_back(curF.getChar());
	}
	return players;
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