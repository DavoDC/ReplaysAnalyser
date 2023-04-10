// Fighter.cpp : 
// Defines Fighter class

// Header file
#include "Fighter.h"

// Namespace mods
using namespace std;


// Global constant - pair separator
const string pairSep = "###$###";

// Initialize static Alias handler
AliasHandler Fighter::aliasHandler;


// Default Constructor
Fighter::Fighter()
{
	pair = StringPair();
}


// Constructs a Fighter from a given string
// e.g. "davo1776 (Wario)"
Fighter::Fighter(string rawPairS)
{
	// Add different separator than white space
	// (Because individual components have spaces as well)
	replaceAll(rawPairS, " (", pairSep);

	// Remove extra bracket at end
	replaceAll(rawPairS, ")", "");
	
	// Split into player and character (2 parts)
	// e.g. 'davo1776' and 'Wario'
	StringV curPairParts = split(rawPairS, pairSep, 2);
	
	// Extract 1st string, the player, and remove whitespace
	string player = curPairParts[0];
	replaceAll(player, " ", "");

	// Handle player aliases
	player = aliasHandler.handlePlayer(player);

	// Extract 2nd string, the character, and remove whitespace
	string character = curPairParts[1];
	replaceAll(character, " ", "");
	
	// Create pair object and save
	StringPair newPair(player, character);
	pair = newPair;
}


// Getters
string Fighter::getPlayer()
{
	return pair.first;
}

string Fighter::getChar()
{
	return pair.second;
}


// Get string representation
string Fighter::toString()
{
	return format("{}({})", getPlayer(), getChar());
}