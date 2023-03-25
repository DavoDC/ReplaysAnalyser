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
FighterList::FighterList(string rawPairS)
{
	// Remove extension
	replaceAll(rawPairS, ".ssfrec", "");

	// Split into individual pairs
	// e.g."davo1776 (Wario)", "HexxaWyn (Naruto)" etc.
	stringV pairs = split(rawPairS, " vs ");

	// If there are not 2, 3 or 4 fighters
	int pLen = int(pairs.size());
	if (!(pLen >= 2 && pLen <= 4))
	{
		print("WARNING: Unusual number of fighters detected");
		print("Fighters: " + to_string(pLen));
	}

	// For every pair string
	for (string curPairS : pairs) {

		// Convert to Fighter and add
		fightersV.push_back(Fighter(curPairS));
	}
}

// ### Getters
// Get the list of players
stringV FighterList::getPlayers()
{
	// Holder
	stringV players;

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
stringV FighterList::getChars()
{
	// Holder
	stringV players;

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
