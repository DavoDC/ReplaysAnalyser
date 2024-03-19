#pragma once

// StatPrinter.h
// Handles printing of statistics information

// Include common
#include "Common.h"

// Include helper classes
#include "Stat.h"
#include "Date.h"

// Declare StatPrinter class
class StatPrinter
{
public:

	// ### Public Methods
	
	// Default Constructor (needed as declaration=instantation for types)
	StatPrinter();

	// Methods
	void printDateStats(Date oldest, Date newest);
	void printStatsList(std::string statName, std::vector<Stat> statList);
	
private:

	// ### Private Methods
	void printStat(Stat stat);
	void printHeading(std::string);
	void printDateColumns(std::string, std::string, std::string);
	void printStatColumns(std::string, std::string, std::string, 
		std::string, std::string);
	std::string formatDateRange(std::string, std::string);
};

