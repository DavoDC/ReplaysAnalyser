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

	// Neb
	StringV neb {
		"B","w","QOZ","i3ssf2","DENT","Morb","joinsomco",
		"NebulaAU","Cocomelon","StuartNeb","NebulaSSBM"
	};
	addAlias("Nebula", neb);

	// Spi
	StringV spi {
		"A","SPI","SPY","Bee","BeeMO",
		"Spii_","SPYRISE","Spyrise","Adriana"
	};
	addAlias("Spi", spi);

	// Jazz
	StringV jazz {
		"P2","JAM","RICE","JASS","JASZ","JazBlue959","JAMMY",
		"CHEESEYJM","JAMVeGMTE","PEANUTJAM", "JAMVEGEMt",
	};
	addAlias("Jazz", jazz);

	// Starboy
	addAlias("Starboy", {
		"x77starboy","MonteSauce","xDuncan", "MetroJr", "ttgmetro"});

	// Epi
	addAlias("Epi", { "LV77","power2","ADEPITA","ACiDTRiP" });

	// Davo
	addAlias("davo", { "P1","DavoDC","davo1776","DAVO1776"});

	// Vink
	addAlias("Vink", { "SkiesFlap","MalonMySwe","MissMyoui" });
	
	// Lost
	addAlias("Lost", { "Lostie","KitKats","Lost-Chan" });

	// Xorop
	addAlias("Xorop", { "xorop53","CR-KING" });

	// Pat
	addAlias("Pat", { "funniswor","stpatboi33" });

	// Egg
	addAlias("Egg", { "TheLegend","T-LegOfEgg" });

	// Singles
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
void AliasHandler::addAlias(string standardName, StringV names)
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