#pragma once

// MatchList.h
// Models a list of SSF2 matches

// Include common
#include "Common.h"

// Include helper classes
#include "Match.h"

// Declare MatchList class
class MatchList
{
public:

	// ### Public Methods
	// Default Constructor (needed as declaration=instantation for types)
	MatchList();
	
	// Constructor
	MatchList(std::string);

	// ### Methods
	void printInfo();
	void sortByDate();

	// # Getters
	int getSize();
	std::string getSizeS();
	std::vector<Match> getMatches();

private:

	// ### Private Fields
	// # Underlying data structure
	std::vector<Match> matches;
};

