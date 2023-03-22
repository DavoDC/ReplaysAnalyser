#pragma once

// Match.h
// Models a SSF2 match

#include "Common.h"

#include <chrono>

class Match
{
public:

	// Constructor
	Match(std::string);


private:

	// # From parent folder:
	// SSF2 version e.g. 1.3.1.2
	std::string version;

	// # From file name:
	// Date of match
	std::chrono::year_month_day date;

	// Player-Character pairs (up to four)
	// use map?

	
};

