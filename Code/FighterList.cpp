// FighterList.cpp : 
// Defines FighterList class

// Header file
#include "FighterList.h"

// Namespace mods
using namespace std;

// Default Constructor
FighterList::FighterList()
{
	fightersV = vector<Fighter>();
}

// Construct FighterList from raw string
// e.g. "davo1776 (Wario) vs HexxaWyn (Naruto) 
// vs FakeNews (Falco) vs x77starboy (Naruto).ssfrec"
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

	// For every pair string
	for (string curPairS : pairs) {

		// Convert to Fighter and add
		fightersV.push_back(Fighter(curPairS));
	}
}

// ### Getters
// Get the list of players
StringV FighterList::getPlayers()
{
	// Holder
	StringV players;

	// For every fighter
	for (Fighter curF : fightersV)
	{
		// Extract and add player
		players.push_back(curF.getPlayer());
	}

	// Return holder
	return players;
}


// Get the list of characters
StringV FighterList::getChars()
{
	// Holder
	StringV players;

	// For every fighter
	for (Fighter curF : fightersV)
	{
		// Extract and add character
		players.push_back(curF.getChar());
	}

	// Return holder
	return players;
}


// Get string representation
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
