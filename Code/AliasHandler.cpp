// AliasHandler.cpp : 
// Defines AliasHandler class

// Header file
#include "AliasHandler.h"

// Namespace mods
using namespace std;

// Name of anonymous player
const std::string AliasHandler::ANON = "ANONY";


// Default Constructor
AliasHandler::AliasHandler()
{
	// Initialize aliases

	// Jazz
	StringV jazz{
		"P2","JAM","JAZ","RICE","JASS","JASZ","JAMm",
		"JazBlue959", "JAMMY", "CHEESEYJM","CHESSJAM",
		"JAMVeGMTE","PEANUTJAM", "JAMVEGEMt", "JAMMEDUP",
		"JAMMED"
	};
	addAlias("Jazz", jazz);

	// Nebula/Rain
	StringV neb{
		"QOZ","rain","DENT","Morb","i3ssf2","joinsomco",
		"NebulaAU","Cocomelon","StuartNeb","NebulaSSBM"
	};
	addAlias("Nebula", neb);

	// Spi
	StringV spi{
		"SPI","SPi","SPY","Bee","BeeMO","AdriBee",
		"Spii_","SPYRISE","Spyrise","Adriana"
	};
	addAlias("Spi", spi);

	// Starboy
	addAlias("Starboy",
		{"x77starboy","MonteSauce","xDuncan", "MetroJr", "ttgmetro" });

	// Davo
	addAlias("davo",
		{ "P1","DAVO","DavoDC","davo1776","DAVO1776", "DISCORD", "davo1776_"});

	// Epi
	addAlias("Epi", { "LV77","power2","ADEPITA","EpiGOAT","ACiDTRiP" });

	// Vink
	addAlias("Vink", { "SkiesFlap","MalonMySwe","MissMyoui" });

	// Lost
	addAlias("Lost", { "Lostie","KitKats","Lost-Chan" });

	// Xorop
	addAlias("Xorop", { "xorop53","CR-KING", "XOROP"});

	// Pat
	addAlias("Pat", { "funniswor","stpatboi33" });

	// Egg
	addAlias("Egg", { "TheLegend","T-LegOfEgg" });

	// Ben
	addAlias("Ben", { "BeetleOven","beetoeoven" });

	// Singles
	addSingleAlias("Cody", "kalakly");
	addSingleAlias("Hexxa", "HexxaWyn");
	addSingleAlias("Malik", "TinMan174");
	addSingleAlias("Jake", "Jakethedog");
	addSingleAlias("JSG", "JustSomeGuy");
	addSingleAlias("Flint", "Flint_the_");
	addSingleAlias("Victor", "MrAgosFan");
	addSingleAlias("Azzie", "InternetSu");
	addSingleAlias("Brubble", "brubblefis");
	addSingleAlias("Lokimazin", "lokimazin");

	// Anonymous player
	addSingleAlias(ANON, "");
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
	// If player name is one character, classify as anonymous
	if (player.size() == 1)
	{
		return ANON;
	}

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