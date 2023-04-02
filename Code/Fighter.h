#pragma once

// Fighter.h
// Models a player-character pair

// Include common
#include "Common.h"

// Macro for long type name
#define StringPair std::pair<std::string, std::string>

class Fighter
{
public:

	// Default Constructor (needed as declaration=instantation for types)
	Fighter();

	// Constructor
	Fighter(std::string);

	// Getters
	std::string getPlayer();
	std::string getChar();

	// Get string representation
	std::string toString();

private:

	// Underlying data structure
	StringPair pair;

	// Helper function
	std::string handleAliases(std::string);
};

