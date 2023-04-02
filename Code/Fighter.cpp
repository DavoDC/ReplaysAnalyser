// Fighter.cpp : 
// Defines Fighter class

// Header file
#include "Fighter.h"

// Namespace mods
using namespace std;

// Global constant - pair separator
const string pairSep = "###$###";

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
	stringV curPairParts = split(rawPairS, pairSep, 2);
	
	// Extract 1st string, the player, and remove whitespace
	string player = curPairParts[0];
	replaceAll(player, " ", "");

	// Handle player aliases
	player = handleAliases(player);

	// Extract 2nd string, the character, and remove whitespace
	string character = curPairParts[1];
	replaceAll(character, " ", "");
	
	// Create pair object and save
	StringPair newPair(player, character);
	pair = newPair;
}


// Handle player aliases by standardizing to a single name
string Fighter::handleAliases(string player)
{
	// Davo
	replaceAll(player, "DavoDC", "davo");
	replaceAll(player, "davo1776", "davo");
	replaceAll(player, "P1", "davo");

	// Jazz
	replaceAll(player, "JAM", "Jazz");
	replaceAll(player, "JazBlue959", "Jazz");
	replaceAll(player, "RICE", "Jazz");
	replaceAll(player, "P2", "Jazz");

	// Pat
	replaceAll(player, "funniswor", "Pat");
	replaceAll(player, "stpatboi33", "Pat");

	// Epi
	replaceAll(player, "ACiDTRiP", "Epi");
	replaceAll(player, "LV77", "Epi");
	replaceAll(player, "power2", "Epi");

	// Spi
	replaceAll(player, "Spii_", "Spi");
	replaceAll(player, "SPI", "Spi");
	replaceAll(player, "SPY", "Spi");
	replaceAll(player, "SPYRISE", "Spi");
	replaceAll(player, "Spyrise", "Spi");
	replaceAll(player, "Adriana", "Spi");
	
	// Lost
	replaceAll(player, "KitKats", "Lost");
	replaceAll(player, "Lost-Chan", "Lost");
	replaceAll(player, "Lostie", "Lost");

	// Neb
	replaceAll(player, "NebulaAU", "Neb");
	replaceAll(player, "NebulaSSBM", "Neb");
	replaceAll(player, "StuartNeb", "Neb");
	replaceAll(player, "i3ssf2", "Neb");

	// Egg
	replaceAll(player, "T-LegOfEgg", "Egg");
	replaceAll(player, "TheLegend", "Egg");

	// Starboy
	replaceAll(player, "xDuncan", "x77starboy");

	// Return final string
	return player;
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
