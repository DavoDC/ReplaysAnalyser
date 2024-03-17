#pragma once

// Stat.h
// Represents a statistic

// Include common
#include "Common.h"

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
	 * @param dateRange Oldest and newest dates for variant's matches
	*/
	Stat(double percentage, VCPair vcPair, StringPair dateRange);

	// ### Getters
	std::string getPercentage() const;
	std::string getVariantValue() const;
	std::string getVariantCount() const;
	std::string getOldestDate() const;
	std::string getNewestDate() const;

private:

	// ### Private Fields
	std::string percentage;
	std::string variantValue;
	std::string variantCount; 
	std::string oldestDate;
	std::string newestDate;
};

