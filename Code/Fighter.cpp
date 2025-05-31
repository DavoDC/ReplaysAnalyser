// Fighter.cpp
#include "Fighter.h"

// Namespace mods
using namespace std;


Fighter::Fighter() : fPair(StringPair())
{
}


Fighter::Fighter(const string& rawPairS)
{
	// Make copy for modification
	string pairCopyS = rawPairS;

	// Add 'Random' character
	replaceAll(pairCopyS, " ()", " (Random)");
	
	// Replace middle part with separator
	replaceAll(pairCopyS, " (", pairSep);

	// Remove extra bracket at end
	replaceAll(pairCopyS, ")", "");

	// Look for a second occurrence of the separator (shouldn't be there)
	size_t pos = pairCopyS.find(pairSep, pairCopyS.find(pairSep) + pairSep.size());

	// If second occurence found, remove everything after it
	if (pos != std::string::npos) {
		pairCopyS.erase(pos);
	}

	// Split into player and character (2 parts)
	// e.g. 'davo1776' and 'Wario'
	StringV curPairParts = split(pairCopyS, pairSep, 2);
	
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


const string Fighter::getPlayer() const
{
	return fPair.first;
}


const string Fighter::getChar() const
{
	return fPair.second;
}


string Fighter::toString() const
{
	return format("{}({})", getPlayer(), getChar());
}