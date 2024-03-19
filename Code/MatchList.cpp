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
	// Holder for version matches
	vector<Match> versionMatches;

	// Copy in version matches using predicate
	std::copy_if(matches.begin(), matches.end(), std::back_inserter(versionMatches),
		[&](Match m)
		{
			// Return true if match's version matches given version
			return m.getVersion() == version;
		}
	);

	// Return result
	return versionMatches;
}


// Get matches played during a certain year
vector<Match> MatchList::getYearMatches(string year)
{
	// Holder for year matches
	vector<Match> yearMatches;

	// Copy in year matches using predicate
	std::copy_if(matches.begin(), matches.end(), std::back_inserter(yearMatches),
		[&](Match m)
		{
			// Return true if match's year matches given year
			return m.getYear() == stoi(year);
		}
	);

	// Return result
	return yearMatches;
}


// Get matches for a given player
// playerName: Standardized player name (after alias handling)
vector<Match> MatchList::getPlayerMatches(string playerName)
{
	// Holder for player's matches
	vector<Match> playerMatches;

	// Copy in player's matches using predicate
	std::copy_if(matches.begin(), matches.end(), std::back_inserter(playerMatches),
		[&](Match m)
		{
			// Return true if the player is found in the match's player list
			return vecContains(m.getFighters().getPlayers(), playerName);
		}
	);

	// Return result
	return playerMatches;
}

// Get matches for a given character
// charName: Character name
vector<Match> MatchList::getCharMatches(string charName)
{
	// Holder for character's matches
	vector<Match> charMatches;

	// Copy in character's matches using predicate
	std::copy_if(matches.begin(), matches.end(), std::back_inserter(charMatches),
		[&](Match m)
		{
			// Return true if the character is found in the match's character list
			return vecContains(m.getFighters().getChars(), charName);
		}
	);

	// Return result
	return charMatches;
}

// Helper for retrieving subsets of matches
// common: Common property in a subset of matches
// FUNCTION: Use same function passed in for freq calcs
// GENERALIZE THIS