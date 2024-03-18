#pragma once

// Match.h
// Models a SSF2 match

// Include common
#include "Common.h"

// Include helper classes
#include "Date.h"
#include "FighterList.h"

// Declare Match class
class Match
{
public:

	// ### Public Methods
	
	// Default Constructor (needed as declaration=instantation for types)
	Match();

	// Constructor
	Match(std::string);

	// Getters
	int getYear();
	Date getDate();
	std::string getYearS();
	std::string getDateS();
	std::string getVersion();
	FighterList getFighters();

	// Get string representation
	std::string toString();

	/**
	 * @return True if this match is newer than the one inputted
	*/
	bool isMatchNewer(Match mInput);


private:

	// ### Private Fields
	// # From parent folder:
	// SSF2 version e.g. 1.3.1.2
	std::string version;

	// # From file name:
	// Date of match
	Date date;

	// Fighters (2, 3 or 4)
	FighterList fighters;
};

