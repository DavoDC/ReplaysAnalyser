#pragma once

// StringPairs.h
// Acts as a wrapper for a vector holding pairs of strings

// Include common
#include "Common.h"

// Macros for long type names
#define PairM std::pair<std::string, std::string>
#define PairsM std::vector<PairM>

class StringPairs
{
public:

	// Default Constructor (needed as declaration = instantation in Match.h)
	StringPairs();

	// Special Constructor
	StringPairs(std::string);

	// Get string representation
	std::string toString();

private:

	// Underlying data structure
	PairsM pairs;
	
	// Helper function for adding pairs
	void addPair(std::string rawPairS);
};

