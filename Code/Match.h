#pragma once

// Match.h
// Models a SSF2 match

// Include common
#include "Common.h"

// Include helper class
#include "ReplayDate.h"

// Macro for type
#define StringPairs std::vector<std::pair<std::string, std::string>>

// Declare Match class
class Match
{
public:
	
	// ### Public Methods
	// Constructor
	Match(std::string);

	// ## Getters
	std::string getVersion();
	ReplayDate getDate();
	StringPairs getPCPairs();

private:

	// ### Private Fields
	// # From parent folder:
	// SSF2 version e.g. 1.3.1.2
	std::string version;

	// # From file name:
	// Date of match
	ReplayDate date;

	// Player-Character pairs (2, 3 or 4)
	StringPairs pcPairs;
};

