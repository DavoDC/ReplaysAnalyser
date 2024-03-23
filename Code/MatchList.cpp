// MatchList.cpp : 
// Defines MatchList class

// Header file
#include "MatchList.h"

// ### Libraries
// # For FS iterator
#include <filesystem>

// # For sort
#include <algorithm>

// # For set
#include <set>

// Namespace mods
using namespace std;
namespace fs = filesystem;

// Macro for long iterator type
#define FSIterator fs::recursive_directory_iterator


// Default Constructor
MatchList::MatchList()
{
	matches = vector<Match>();
}


// Construct a match list from a directory path
MatchList::MatchList(string replayPath)
{
	// If path is not valid
	// (This is done here since the filesystem lib is here already)
	if (!fs::exists(replayPath))
	{
		// Notify and exit
		print("\nMatchList(): Invalid Replay Path");
		print("\nPath was: " + replayPath + "\n");
		exit(EXIT_FAILURE);
	}

	// Check
	bool foundOneReplay = false;

	// For every path in the directory
	for (const auto& curPath : FSIterator(replayPath)) {

		// Convert current path to string
		string curPathS = curPath.path().generic_string();

		// If it is a replay path/file
		if (contains(curPathS, ".ssfrec")) {

			// Update check
			foundOneReplay = true;

			// Convert to Match and add to list
			matches.push_back(Match(curPathS));
		}
	}

	// If didn't find at least one replay
	if (!foundOneReplay)
	{
		// Notify and exit
		print("\nMatchList(): Empty Replay Folder");
		print("\nNo replays found!");
		print("\nPath was: " + replayPath + "\n");
		exit(EXIT_FAILURE);
	}

	// Sort matches by date
	sort(matches.begin(), matches.end(),
		[](Match m1, Match m2) {

			return m2.isMatchNewer(m1);
		});
}


// Print out all match info
void MatchList::printInfo()
{
	for (Match curM : matches)
	{
		print(curM.toString());
	}
}


// ## Getters

// Get number of matches in list
int MatchList::getSize()
{
	return int(matches.size());
}

// Get underlying vector
vector<Match> MatchList::getMatches()
{
	return matches;
}

// Get date of first match
Date MatchList::getFirstMatchDate()
{
	return matches.front().getDate();
}

// Get date of last match
Date MatchList::getLastMatchDate()
{
	return matches.back().getDate();
}


// Get matches played on a given version of the game
vector<Match> MatchList::getVersionMatches(string version)
{
	return getVariantMatches([&](Match lm)
		{
			return lm.getVersion() == version;
		});
}


// Get matches played during a certain year
vector<Match> MatchList::getYearMatches(string year)
{
	return getVariantMatches([&](Match lm)
		{
			return lm.getYear() == stoi(year);
		});
}


// Get matches for a given player
// playerName: Standardized player name (after alias handling)
vector<Match> MatchList::getPlayerMatches(string playerName)
{
	return getVariantMatches([&](Match lm)
		{
			return vecContains(lm.getFighters().getPlayers(), playerName);
		});
}

// Get matches for a given character
// charName: Character name
vector<Match> MatchList::getCharMatches(string charName)
{
	return getVariantMatches([&](Match lm)
		{
			return vecContains(lm.getFighters().getChars(), charName);
		});
}

// Helper for retrieving a variant's matches
// variantValue: The variant's values
vector<Match> MatchList::getVariantMatches(VarMatchChecker hasVariant)
{
	// Holder for the variant's matches
	vector<Match> variantMatches;

	// Copy in match if it has the variant
	std::copy_if(matches.begin(), matches.end(), std::back_inserter(variantMatches),
		[&](Match m)
		{
			return hasVariant(m);
		}
	);

	// Return result
	return variantMatches;
}