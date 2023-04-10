#pragma once

// FighterList.h
// Models a list of fighters

// Include common
#include "Common.h"

// Include sub-component
#include "Fighter.h"

class FighterList
{
public:

	// Default Constructor (needed as declaration=instantation for types)
	FighterList();

	// Constructor
	FighterList(std::string);

	// Getters
	StringV getPlayers();
	StringV getChars();

	// Get string representation
	std::string toString();

private:

	// Underlying data structure
	std::vector<Fighter> fightersV;
};

