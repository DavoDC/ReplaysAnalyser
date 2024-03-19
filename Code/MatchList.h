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
	// Default Constructor (needed as declaration=instantiation for types)
	MatchList();
	
	// Constructor
	MatchList(std::string);

	// ### Methods
	void printInfo();

	// # Getters
	int getSize();
	std::vector<Match> getMatches();
	Date getFirstMatchDate();
	Date getLastMatchDate();
	std::vector<Match> getVersionMatches(std::string);
	std::vector<Match> getYearMatches(std::string);
	std::vector<Match> getPlayerMatches(std::string);
	std::vector<Match> getCharMatches(std::string);

private:

	// ### Private Fields
	// # Underlying data structure
	std::vector<Match> matches;

	// ### Private Methods
	//std::vector<Match> getCertainMatches(std::string);
};

