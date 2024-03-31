#pragma once

// MatchList.h
// Models a list of SSF2 matches

#include "Common.h"
#include "Match.h"
#include <functional>

// Returns true if the match contains a given variant
#define VarMatchChecker std::function<bool(Match)>


// Declare MatchList class
class MatchList
{
public:

	// ### Public Methods
	// Default Constructor (needed as declaration=instantiation for types)
	MatchList();
	
	// Constructor
	MatchList(std::string, bool);

	// ### Methods
	void printInfo();

	// # Getters
	int getSize();
	std::string getSizeS();
	Date getLastMatchDate();
	Date getFirstMatchDate();
	std::vector<Match> getMatches();
	std::vector<Match> getYearMatches(std::string);
	std::vector<Match> getCharMatches(std::string);
	std::vector<Match> getPlayerMatches(std::string);
	std::vector<Match> getVersionMatches(std::string);

private:

	// ### Private Fields
	// # Underlying data structure
	std::vector<Match> matches;

	// ### Private Methods
	std::vector<Match> getVariantMatches(VarMatchChecker);
};

