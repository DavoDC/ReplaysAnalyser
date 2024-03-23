// Stat.cpp : 
// Defines Stat class

// Header file
#include "Stat.h"

// Namespace mods
using namespace std;

// Default Constructor
Stat::Stat()
{
}

// Construct a statistics object
Stat::Stat(double percentage, VCPair vcPair, vector<Match> varMList)
{
	// Notify and stop if matchlist empty
	if (varMList.empty())
	{
		print("Empty matchlist provided to Stat!");
		return;
	}

	// Process and save percentage 
	this->percentageS = to_string(percentage).erase(4) + "%";

	// Extract and save variant and count values
	this->variantValue = vcPair.first;
	this->variantCountS = to_string(vcPair.second);

	// Calculate and save oldest and newest matches
	auto dateRangePair = minmax_element(
		varMList.begin(), varMList.end(),
		[](Match m1, Match m2) {
			return m2.isMatchNewer(m1);
		});
	Date oldestDate = dateRangePair.first._Ptr->getDate();
	Date newestDate = dateRangePair.second._Ptr->getDate();
	oldestDateS = oldestDate.toString();
	newestDateS = newestDate.toString();

	// Get and save duration
	durationS = oldestDate.getAbsDuration(newestDate);
}

// ### Getters
std::string Stat::getPercentage() const
{
	return percentageS;
}

std::string Stat::getVariantValue() const
{
	return variantValue;
}

std::string Stat::getVariantCount() const
{
	return variantCountS;
}

std::string Stat::getOldestDate() const
{
	return oldestDateS;
}

std::string Stat::getNewestDate() const
{
	return newestDateS;
}

std::string Stat::getDuration() const
{
	return durationS;
}