#pragma once

// Fighter.h
// Models a player-character pair

// Include common
#include "Common.h"

// Include Alias Handler
#include "AliasHandler.h"


class Fighter
{
public:

	// # Constructors
	// Default Constructor (needed as declaration=instantation for types)
	Fighter();

	// Constructor
	Fighter(std::string);

	// # Public methods
	// Getters
	std::string getPlayer();
	std::string getChar();

	// Get string representation
	std::string toString();

private:

	// # Private fields
	// Underlying data structure
	StringPair pair;

	// Alias handler
	// (Static since it will be the same for the entire runtime)
	// (Constructor only runs once, more efficient)
	static AliasHandler aliasHandler;
};

