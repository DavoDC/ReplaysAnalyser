#pragma once

// StatList.h
// Represents a statistics calculator

// Include common
#include "Common.h"

// Include helper classes
#include "MatchList.h"
#include "Match.h"
#include "Stat.h"


// ### Libraries
#include <functional>
#include <map>
#include <algorithm>


// ### Macros
// Match property extractor
#define PropExt std::function<StringV(Match)>

// Variant match list extractor (list of matches with a certain variant)
#define MatchVExt std::function<std::vector<Match>(MatchList, std::string)>

// Variant-Count pair
#define VCPair std::pair<std::string, int>


// Declare StatList class
class StatList
{
public:

	// ### Public Methods
	// Default Constructor (needed as declaration=instantiation for types)
	StatList();
	
	/**
	 * @brief Construct a list of statistics
	 * @param matchList The full match list 
	 * @param propExt Extracts the property from a match
	 * @param ignore A list of variants to ignore
	 * @param cutoff Percentage cutoff used to exclude variants
	 * @param matchVExt Extract list of matches with variant from matchlist
	*/
	StatList(MatchList matchList, PropExt propExt, StringV ignore,
		double cutoff, MatchVExt matchVExt);

	// ### Getter
	std::vector<Stat> getStatList();

private:

	// ### Private Fields
	// Underlying data structure
	std::vector<Stat> statList;

	// ### Private Methods
	StringPair getDateRangeForMatches(std::vector<Match> matchList);
};

