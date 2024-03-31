// Fighter.cpp
#include "Fighter.h"

// Namespace mods
using namespace std;


Fighter::Fighter()
{
	fPair = StringPair();
}


Fighter::Fighter(string rawPairS)
{
	// Add 'Random' character
	replaceAll(rawPairS, " ()", " (Random)");
	
	// Replace middle part with separator
	replaceAll(rawPairS, " (", pairSep);

	// Remove extra bracket at end
	replaceAll(rawPairS, ")", "");

	// Look for a second occurrence of the separator (shouldn't be there)
	size_t pos = rawPairS.find(pairSep, rawPairS.find(pairSep) + pairSep.size());

	// If second occurence found, remove everything after it
	if (pos != std::string::npos) {
		rawPairS.erase(pos);
	}

	// Split into player and character (2 parts)
	// e.g. 'davo1776' and 'Wario'
	StringV curPairParts = split(rawPairS, pairSep, 2);
	
	// Extract 1st string, the player name, and remove whitespace
	string player = curPairParts[0];
	replaceAll(player, " ", "");

	// Standardise the player's name, accounting for aliases
	player = AliasHandler::getStandardName(player);

	// Extract 2nd string, the character, and remove whitespace
	string character = curPairParts[1];
	replaceAll(character, " ", "");
	
	// Create pair object and save
	fPair = make_pair(player, character);
}


string Fighter::getPlayer()
{
	return fPair.first;
}


string Fighter::getChar()
{
	return fPair.second;
}


string Fighter::toString()
{
	return format("{}({})", getPlayer(), getChar());
}