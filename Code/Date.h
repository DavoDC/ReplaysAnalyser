#pragma once

// Date.h
// Acts as a wrapper for standard Date class

// Include common
#include "Common.h"

// ### Libraries
#include <chrono>

// Macro for long type name
#define DateM std::chrono::year_month_day


// Declare Date class
class Date
{

public:

	// Default Constructor (needed as declaration=instantation for types)
	Date();

	// Special Constructors
	Date(std::string);
	Date(DateM);

	// Retrieve internal date
	DateM getYMD();

	// Convert to string
	std::string toString();
private:

	// Internal standard date object
	DateM intYMD;

};

