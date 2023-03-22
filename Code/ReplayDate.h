#pragma once

// ReplayDate.h
// Extends standard Date class

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
    std::chrono::year_month_day getDate();
private: 

	// Internal standard date object
	std::chrono::year_month_day internalDate;

};

