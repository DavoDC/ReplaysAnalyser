#pragma once

// StatPrinter.h
// Handles printing of statistics information

// Include common
#include "Common.h"

// Include helper classes
#include "Stat.h"

// Declare StatPrinter class
class StatPrinter
{
public:

	// ### Public Methods
	
	// Default Constructor (needed as declaration=instantation for types)
	StatPrinter();

	// Methods
	void printHeading(std::string);
	void printCurDate(std::string);
	void printDateRange(std::string, std::string);
	void printStatsList(std::vector<Stat> statList);
	

private:

	// ### Private Methods
	std::string formatDateRange(std::string, std::string);
	void printColumns(std::string, std::string, std::string, std::string);
	void printStat(Stat stat);
};

