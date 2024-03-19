#pragma once

// Stat.h
// Represents a statistic

// Include common
#include "Common.h"
#include "Match.h"

// Libraries
#include <algorithm>

// ### Macros
// Variant-Count pair
#define VCPair std::pair<std::string, int>


// Declare Stat class
class Stat
{
public:

	// ### Public Methods
	// Default Constructor (needed as declaration=instantiation for types)
	Stat();
	
	/**
	 * @brief Construct a statistic object
	 * @param percentage Of matches with the variant 
	 * @param vcPair A variant-count pair
	 * @param varMList The matches with the variant
	*/
	Stat(double percentage, VCPair vcPair, std::vector<Match> varMList);

	// ### Getters
	std::string getPercentage() const;
	std::string getVariantValue() const;
	std::string getVariantCount() const;
	std::string getOldestDate() const;
	std::string getNewestDate() const;
	std::string getDuration() const;

private:

	// ### Private Fields
	std::string percentageS;
	std::string variantValue;
	std::string variantCountS; 
	std::string oldestDateS;
	std::string newestDateS;
	std::string durationS;
};

