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

	// Sort vector of matches using comparison function
	// https://cplusplus.com/reference/algorithm/sort/
	sort(matches.begin(), matches.end(),
		[](Match m1, Match m2) {

			// Return 'greater' internal date
			return (m1.getDate().getYMD() < m2.getDate().getYMD());
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

// Get size as an int
int MatchList::getSize()
{
	return int(matches.size());
}

// Get size as a string
std::string MatchList::getSizeS()
{
	return to_string(getSize());
}

// Get matches
vector<Match> MatchList::getMatches()
{
	return matches;
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
			// Extract player list from match
			vector<string> playerList = m.getFighters().getPlayers();

			// Return true if player is found in player list
			return count(playerList.begin(), playerList.end(), playerName) != 0;
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
			// Extract character list from match
			vector<string> charList = m.getFighters().getChars();

			// Return true if character is found in character list
			return count(charList.begin(), charList.end(), charName) != 0;
		}
	);

	// Return result
	return charMatches;
}

// Helper for retrieving subsets of matches
// common: Common property in a subset of matches
// FUNCTION: Use same function passed in for freq calcs
//vector<Match> MatchList::getCertainMatches(string common, FUNCTION)
//{
//	// Holder for match subset
//	vector<Match> matchSubset;
//
//	// Copy matches into holder that possess a given common property
//	std::copy_if(matches.begin(), matches.end(), std::back_inserter(matchSubset),
//		[&](Match m)
//		{
//			// Extract list of the relevant properties
//			vector<string> propList = func(m);
//
//			// Return true if value is found in properties
//			return count(propList.begin(), propList.end(), common) != 0;
//		}
//	);
//
//	// Return result
//	return matchSubset;
//}