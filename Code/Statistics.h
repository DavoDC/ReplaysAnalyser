#pragma once

// Statistics.h
// Represents a statistics calculator

// Include common
#include "Common.h"

// Include helper classes
#include "MatchList.h"
#include "Match.h"

// ### Libraries
// For function type
#include <functional>

// ### Macros
// Match property extractor
#define Extractor std::function<StringV(Match)>


// Declare Statistics class
class Statistics
{
public:

	// ### Public Methods
	// Default Constructor (needed as declaration=instantiation for types)
	Statistics();
	
	// Constructor
	Statistics(const std::string, const MatchList& mlRef, const Extractor);
private:

	// ### Private Fields
	// # The name of the property that statistics are being calculated for 
	const std::string name;

	// # A reference to the match list 
	const MatchList& mlRef;

	// # A function that extracts the relevant property from a match 
	const Extractor matchProp;
};

