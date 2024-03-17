// StatList.cpp : 
// Defines StatList class

// Header file
#include "StatList.h"

// Namespace mods
using namespace std;

// Default Constructor
StatList::StatList()
{
}

// Construct a list of statistics objects
StatList::StatList(MatchList matchList, PropExt propExt, StringV ignore,
	double cutoff, MatchVExt matchVExt)
{
	// Extract match list info
	vector<Match> matches = matchList.getMatches();
	int matchNum = matchList.getSize();

	// Create map of unique strings paired with how many there are
	map<string, int> itemVariants;
	for (Match curMatch : matches)
	{
		// Extract string properties using the function given (e.g. player names)
		StringV curProps = propExt(curMatch);

		// For each string property
		for (string curS : curProps)
		{
			// If current property not in ignore list
			if (!vecContains(ignore, curS))
			{
				// Increment the count of the variant (or add it to the map)
				itemVariants[curS]++;
			}
		}
	}

	// Convert the map to a vector of pairs (since maps cannot be sorted)
	vector<VCPair> itemVariantsV(itemVariants.begin(), itemVariants.end());

	// Sort the variants, placing the highest count variants at the top
	sort(itemVariantsV.begin(), itemVariantsV.end(),
		[](const VCPair pair1, const VCPair pair2) {
			// Return true if pair has higher count
			return pair1.second > pair2.second;
		});

	// Iterate over pairs to create statistics objects
	for (VCPair curPair : itemVariantsV)
	{
		// Calculate the percentage of matches with the variant
		double percentage = ((double)curPair.second / (double)matchNum) * 100;

		// If percentage significant
		if (percentage > cutoff)
		{
			// Get date range string pair
			StringPair dateRange = getDateRangeForMatches(matchVExt(matchList, curPair.first));
			
			// Create stats object and add to list
			statList.push_back(Stat(percentage, curPair, dateRange));
		}
	}
}


// Extract underlying data structure
vector<Stat> StatList::getStatList()
{
	return statList;
}


// Helper: Get date range string pair for a given match list
StringPair StatList::getDateRangeForMatches(vector<Match> matchList)
{
	// Find oldest and newest matches
	auto dateRangePair = std::minmax_element(matchList.begin(), matchList.end(),
		[](Match m1, Match m2) {
			// Return 'greater' internal date
			return (m1.getDate().getYMD() < m2.getDate().getYMD());
		});

	// Convert to strings and pair together
	return StringPair(dateRangePair.first._Ptr->getDate().toString(),
		dateRangePair.second._Ptr->getDate().toString());
}