// Stat.cpp
#include "Stat.h"

// Namespace mods
using namespace std;


Stat::Stat()
{
}


Stat::Stat(const double& percentage, const VCPair& vcPair,
	const vector<Match>& varMList)
{
	// Process and save percentage
	this->percentageS = to_string(percentage).erase(4) + "%";
	if (percentage >= 100)
	{
		this->percentageS = "100%";
	}

	// Extract and save variant and count values
	this->variantValue = vcPair.first;
	this->variantCountS = to_string(vcPair.second);

	// Notify and stop if matchlist empty
	if (varMList.empty())
	{
		print("Empty variant matchlist provided to Stat!");
		return;
	}

	// Convert and save variant matchlist
	variantMatchList = MatchList(varMList);

	// Calculate and save oldest and newest matches
	auto dateRangePair = minmax_element(
		varMList.begin(), varMList.end(),
		[](const Match& m1, const Match& m2) {
			return m2.isMatchNewer(m1);
		});
	this->oldestDate = dateRangePair.first._Ptr->getDate();
	this->newestDate = dateRangePair.second._Ptr->getDate();

	// Get and save duration
	timePeriodS = oldestDate.getAbsTimePeriod(newestDate);
}


string Stat::getPercentage() const
{
	return percentageS;
}


string Stat::getVariantValue() const
{
	return variantValue;
}


string Stat::getVariantCount() const
{
	return variantCountS;
}

MatchList Stat::getVariantMatchList() const
{
	return variantMatchList;
}


Date Stat::getOldestDate() const
{
	return oldestDate;
}


Date Stat::getNewestDate() const
{
	return newestDate;
}


string Stat::getTimePeriod() const
{
	return timePeriodS;
}