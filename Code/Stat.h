#pragma once

// Stat.h
// Represents a statistic

#include "Common.h"
#include "Match.h"
#include <algorithm>

// Variant-Count pair
#define VCPair std::pair<std::string, int>


class Stat
{
public:

	/**
	 * @brief Construct an empty stat object
	*/
	Stat();
	
	/**
	 * @brief Construct a statistic object
	 * @param percentage Of matches with the variant 
	 * @param vcPair A variant-count pair
	 * @param varMList The matches with the variant
	*/
	Stat(const double& percent, const VCPair& vcPair, const std::vector<Match>& varMList);

	/**
	 * @return The percentage of matches with the variant as a string
	*/
	std::string getPercentage() const;

	/**
	 * @return The variant's value
	*/
	std::string getVariantValue() const;

	/**
	 * @return The number of times this variant occurs
	*/
	std::string getVariantCount() const;

	/**
	 * @return The oldest match date for this variant's matches
	*/
	Date getOldestDate() const;

	/**
	 * @return The latest match date for this variant's matches
	*/
	Date getNewestDate() const;

	/**
	 * @return The time/date period for this variant's matches
	*/
	std::string getTimePeriod() const;

private:

	/**
	 * @brief The percentage of matches with the variant as a string
	*/
	std::string percentageS;

	/**
	 * @brief The variant's value
	*/
	std::string variantValue;

	/**
	 * @brief The number of times this variant occurs
	*/
	std::string variantCountS; 

	/**
	 * @brief The oldest match date for this variant's matches
	*/
	Date oldestDate;

	/**
	 * @brief The latest match date for this variant's matches
	*/
	Date newestDate;

	/**
	 * @brief The time/date period for this variant's matches
	*/
	std::string timePeriodS;
};

