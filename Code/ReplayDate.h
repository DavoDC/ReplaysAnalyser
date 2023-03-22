#pragma once

// ReplayDate.h
// Acts as a wrapper for standard Date class

// Include common
#include "Common.h"

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
    std::chrono::year_month_day getYMD();

	// Convert to string
	std::string toString();
private: 

	// Internal standard date object
	std::chrono::year_month_day YMD;

};

