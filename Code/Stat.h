#pragma once

// Stat.h

#include "Common.h"
#include "Match.h"
#include "MatchList.h"
#include <algorithm>

// Variant-Count pair
using VCPair = std::pair<std::string, int>;

/**
 * @brief Represents a frequency statistic
 */
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
	const std::string& getPercentage() const;

	/**
	 * @return The variant's value
	*/
	const std::string& getVariantValue() const;

	/**
	 * @return The number of times this variant occurs
	*/
	const std::string& getVariantCount() const;

	/**
	 * @brief A list of matches with the variant
	*/
	const MatchList& getVariantMatchList() const;

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
	const std::string& getTimePeriod() const;

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
	 * @brief A list of matches with the variant
	*/
	MatchList variantMatchList;

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

