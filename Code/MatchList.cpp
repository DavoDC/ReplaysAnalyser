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

// Macro for long iterator type
#define FSIterator filesystem::recursive_directory_iterator

// Namespace mods
using namespace std;


// Default Constructor
MatchList::MatchList()
{
	matches = vector<Match>();
}


// Construct a match list from a directory path
MatchList::MatchList(string replayPath)
{
	// For every path in the directory
	for (const auto& curPath : FSIterator(replayPath)) {

		// Convert current path to string
		string curPathS = curPath.path().generic_string();

		// If it is a replay path/file
		if (contains(curPathS, ".ssfrec")) {

			// Convert to Match and add to list
			matches.push_back(Match(curPathS));
		}
	}
}




// Sort by date
void MatchList::sortByDate()
{
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
