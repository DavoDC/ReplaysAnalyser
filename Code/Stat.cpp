// Stat.cpp
#include "Stat.h"

// Namespace mods
using namespace std;


Stat::Stat()
{
}


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
	if (percentage >= 100)
	{
		this->percentageS = "100%";
	}

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
	timePeriodS = oldestDate.getAbsTimePeriod(newestDate);
}


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


std::string Stat::getTimePeriod() const
{
	return timePeriodS;
}