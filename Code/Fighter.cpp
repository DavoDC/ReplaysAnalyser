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

	// Handle empty player
	if (player.compare("") == 0)
	{
		player = "ANON";
	}

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
	// Spi (7)
	replaceAll(player, "Spii_", "Spi");
	replaceAll(player, "SPYRISE", "Spi");
	replaceAll(player, "Spyrise", "Spi");
	replaceAll(player, "Adriana", "Spi");
	replaceAll(player, "SPI", "Spi");
	replaceAll(player, "SPY", "Spi");
	if (player.compare("A") == 0)
	{
		replaceAll(player, "A", "Spi");
	}

	// Epi (4)
	replaceAll(player, "ACiDTRiP", "Epi");
	replaceAll(player, "LV77", "Epi");
	replaceAll(player, "power2", "Epi");
	replaceAll(player, "ADEPITA", "Epi");

	// Jazz (4)
	replaceAll(player, "JAM", "Jazz");
	replaceAll(player, "JazBlue959", "Jazz");
	replaceAll(player, "RICE", "Jazz");
	replaceAll(player, "P2", "Jazz");

	// Neb (4)
	replaceAll(player, "NebulaAU", "Neb");
	replaceAll(player, "NebulaSSBM", "Neb");
	replaceAll(player, "StuartNeb", "Neb");
	replaceAll(player, "i3ssf2", "Neb");

	// Davo (3)
	replaceAll(player, "DavoDC", "davo");
	replaceAll(player, "davo1776", "davo");
	replaceAll(player, "P1", "davo");

	// Lost (3)
	replaceAll(player, "KitKats", "Lost");
	replaceAll(player, "Lost-Chan", "Lost");
	replaceAll(player, "Lostie", "Lost");

	// Pat (2)
	replaceAll(player, "funniswor", "Pat");
	replaceAll(player, "stpatboi33", "Pat");

	// Egg (2)
	replaceAll(player, "T-LegOfEgg", "Egg");
	replaceAll(player, "TheLegend", "Egg");

	// Starboy (1)
	replaceAll(player, "xDuncan", "x77starboy");

	// Azzie (1)
	replaceAll(player, "InternetSu", "Azzie");

	// Hexxa (1)
	replaceAll(player, "HexxaWyn", "Hexxa");

	// Jake (1)
	replaceAll(player, "Jakethedog", "Jake");

	// Victor (1)
	replaceAll(player, "MrAgosFan", "Victor");
		
	// Brubble (1)
	replaceAll(player, "brubblefis", "brubble");

	// Cody (1)
	replaceAll(player, "kalakly", "Cody");

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
