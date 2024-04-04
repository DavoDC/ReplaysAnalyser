// AliasHandler.cpp
#include "AliasHandler.h"

// Namespace modifier
using namespace std;

// Initialise static variables
const string AliasHandler::ANON = "ANON";
string AliasHandler::p1Name = "davo";
string AliasHandler::p2Name = "Jazz";
vector<Alias> AliasHandler::aliases;


const void AliasHandler::setOfflinePlayerNames(const string& p1Name, 
	const string& p2Name)
{
	AliasHandler::p1Name = p1Name;
	AliasHandler::p2Name = p2Name;
}


void AliasHandler::initAliases()
{
	// If aliases are already initialised, stop
	if (!aliases.empty())
	{
		return;
	}

	// Add offline player aliases
	addSingleAlias(p1Name, "P1");
	addSingleAlias(p2Name, "P2");

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

	// Simple aliases
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
}


void AliasHandler::addSingleAlias(const string& standardName, const string& oldName)
{
	addAlias(standardName, { oldName });
}


void AliasHandler::addAlias(const string& standardName, const StringV& names)
{
	// Create pair then add to vector
	aliases.push_back(make_pair(standardName, names));
}


const string AliasHandler::getStandardName(const string& pName)
{
	// Initialise aliases, if needed
	initAliases();

	// If player name is empty or one character, classify as anonymous
	if (pName.empty() || pName.size() == 1)
	{
		return ANON;
	}

	// Initialise new name to original in case no alias is found
	string newName = pName;

	// For every alias
	for (Alias curAlias : aliases)
	{
		// For every raw/unstandardised/actual name in the alias
		for (string rawName : curAlias.second)
		{
			// If the player's name matches a raw name
			if (equalsIgnoreCase(pName, rawName))
			{
				// Set player name to standard name
				newName = curAlias.first;

				// Stop iterating
				break;
			}
		}
	}

	// Return new name
	return newName;
}