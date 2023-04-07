// AliasHandler.cpp : 
// Defines AliasHandler class

// Header file
#include "AliasHandler.h"

// Namespace mods
using namespace std;


// Default Constructor
AliasHandler::AliasHandler()
{
	// Initialize aliases

	// Spi (7)
	stringV spi {"A","SPI","SPY","Spii_","SPYRISE","Spyrise","Adriana"};
	addAlias("Spi", spi);

	// Epi (4)
	addAlias("Epi", { "LV77","power2","ADEPITA","ACiDTRiP" });

	// Jazz (4)
	addAlias("Jazz", { "P2","JAM","RICE","JazBlue959" });

	// Neb (4)
	addAlias("Nebula", { "i3ssf2","NebulaAU","StuartNeb","NebulaSSBM" });

	// Davo (3)
	addAlias("davo", {"P1","DavoDC","davo1776"});
	
	// Lost (3)
	addAlias("Lost", { "Lostie","KitKats","Lost-Chan" });

	// Pat (2)
	addAlias("Pat", { "funniswor","stpatboi33" });

	// Egg (2)
	addAlias("Egg", { "TheLegend", "T-LegOfEgg" });

	// Singles
	addSingleAlias("x77starboy", "xDuncan");
	addSingleAlias("Azzie", "InternetSu");
	addSingleAlias("Hexxa", "HexxaWyn");
	addSingleAlias("Jake", "Jakethedog");
	addSingleAlias("Victor", "MrAgosFan");
	addSingleAlias("brubble", "brubblefis");
	addSingleAlias("Cody", "kalakly");

	// Empty player
	addSingleAlias("ANON", "");
}


// Helper/wrapper for adding one-to-one aliases
void AliasHandler::addSingleAlias(string standardName, string oldName)
{
	addAlias(standardName, { oldName });
}

// Helper/wrapper for adding one-to-many aliases
void AliasHandler::addAlias(string standardName, stringV names)
{
	// Call vector add and pair creation functions
	aliases.push_back(make_pair(standardName, names));
}


// Handle a given player name
string AliasHandler::handlePlayer(string player)
{
	// Holder
	// (Initialize to original in case no alias is found)
	string newName = player;

	// For every alias
	for (Alias curAlias : aliases)
	{
		// For every raw name (unstandardized, actual names)
		for (string rawName : curAlias.second)
		{
			// If the player's name is a perfect match
			if (player == rawName)
			{
				// Set player name to standard name
				newName = curAlias.first;

				// Equivalent to 'assign()', see here:
				// https://stackoverflow.com/q/34196053/17869538

				// Stop iterating
				break;
			}
		}
	}

	// Return new name
	return newName;
}