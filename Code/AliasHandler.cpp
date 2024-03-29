// AliasHandler.cpp : 
// Defines AliasHandler class

// Header file
#include "AliasHandler.h"

// Namespace mods
using namespace std;

// Name of anonymous player
const std::string AliasHandler::ANON = "ANON";

// Set default offline player aliases
std::string AliasHandler::p1Alias = "davo";
std::string AliasHandler::p2Alias = "Jazz";


// Default Constructor
AliasHandler::AliasHandler()
{
	// Initialize aliases

	// Jazz
	StringV jazz{
		"JAM","JAZ","RICE","JASS","JASZ","JAMm",
		"JazBlue959","JAMMY","CHEESEYJM","CHESSJAM",
		"JAMVeGMTE","PEANUTJAM","JAMVEGEMt","JAMMEDUP",
		"JAMMED"
	};
	addAlias("Jazz", jazz);

	// Spi
	StringV spi{
		"Spi","SPY","Spii","Spii_","Spii329","Spyrise",
		"Bee","BeeMO", "BeeMO3","Bee3",
		"Adri","AdriBee","AdriOnTop","Adriana","Adriana3"
	};
	addAlias("Spi", spi);

	// Nebula/Rain
	StringV neb{
		"Neb","May","QOZ","rain","DENT","Morb",
		"i3ssf2","joinsomco","NebulaAU","Cocomelon",
		"StuartNeb","NebulaSSBM","rain93226",
	};
	addAlias("Nebula", neb);

	// Starboy
	addAlias("Starboy",
		{
			"x77starboy","MonteSauce","xDuncan", "MetroJr", "ttgmetro"
		});

	// Davo
	addAlias("davo", { "DAVO", "davo1776","davo1776_","DavoDC","DISCORD" });

	// Epi
	addAlias("Epi", { "LV77","power2","ADEPITA","EpiGOAT","ACiDTRiP" });

	// Vink
	addAlias("Vink", { "SkiesFlap","MalonMySwe","MissMyoui" });

	// Lost
	addAlias("Lost", { "Lostie","KitKats","Lost-Chan" });

	// Xorop
	addAlias("Xorop", { "xorop53","CR-KING", "XOROP" });

	// Pat
	addAlias("Pat", { "funniswor","stpatboi33" });

	// Egg
	addAlias("Egg", { "TheLegend","T-LegOfEgg" });

	// Ben
	addAlias("Ben", { "BeetleOven","beetoeoven" });

	// Singles
	addSingleAlias("Cody", "kalakly");
	addSingleAlias("Hexxa", "HexxaWyn");
	addSingleAlias("Jake", "Jakethedog");
	addSingleAlias("JSG", "JustSomeGuy");
	addSingleAlias("Malik", "TinMan174");
	addSingleAlias("Flint", "Flint_the_");
	addSingleAlias("Victor", "MrAgosFan");
	addSingleAlias("Azzie", "InternetSu");
	addSingleAlias("Brubble", "brubblefis");
	addSingleAlias("Lokimazin", "lokimazin");

	// Handle offline player aliases
	addSingleAlias(p1Alias, "P1");
	addSingleAlias(p2Alias, "P2");
}


void AliasHandler::setOfflinePlayerAliases(string p1name, string p2name)
{
	p1Alias = p1name;
	p2Alias = p2name;
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
	// If player name is empty or one character, classify as anonymous
	if (player.empty() || player.size() == 1)
	{
		return ANON;
	}

	// Initialize new name to original in case no alias is found
	string newName = player;

	// For every alias
	for (Alias curAlias : aliases)
	{
		// For every raw/unstandardized/actual name in the alias
		for (string rawName : curAlias.second)
		{
			// If the player's name matches a raw name
			if (equalsIgnoreCase(player, rawName))
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