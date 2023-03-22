#pragma once

// Match.h
// Models a SSF2 match

// Include common
#include "Common.h"

// Include helper class
#include "ReplayDate.h"


// Declare Match class
class Match
{
public:
	
	// ### Public Methods
	// Constructor
	Match(std::string);


private:

	// ### Private Fields
	// # From parent folder:
	// SSF2 version e.g. 1.3.1.2
	std::string version;

	// # From file name:
	// Date of match
	ReplayDate date;

	// Player-Character pairs (up to four)
	// use map?
};

