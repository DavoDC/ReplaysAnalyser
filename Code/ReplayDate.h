#pragma once

// ReplayDate.h
// Acts as a wrapper for standard Date class

// Include common
#include "Common.h"

// Macro for long type name
#define DateM std::chrono::year_month_day

// ### Libraries
#include <chrono>

// Declare ReplayDate class
class ReplayDate
{

public:

	// Default Constructor (needed as declaration = instantation in Match.h)
	ReplayDate();

	// Special Constructor
	ReplayDate(std::string);

	// Retrieve internal date
	DateM getYMD();

	// Convert to string
	std::string toString();
private:

	// Internal standard date object
	DateM YMD;

};

