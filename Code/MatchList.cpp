// MatchList.cpp : 
// Defines MatchList class

// Header file
#include "MatchList.h"

// Namespace mods
using namespace std;

// Macro for long iterator type
#define FSIterator filesystem::recursive_directory_iterator


// Construct a match list from a directory path
MatchList::MatchList(string replayPath)
{
	// For every path in the directory
	for (const auto& curPath : FSIterator(replayPath)) {

		// Convert current path to string
		string curPathS = curPath.path().generic_string();

		// If it is a replay path/file
		if (strstr(curPathS.c_str(), ".ssfrec")) {

			// Convert to Match and add to list
			matches.push_back(Match(curPathS));
		}
	}
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


