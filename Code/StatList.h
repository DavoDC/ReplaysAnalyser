#pragma once

// StatList.h
// Represents a statistics calculator

#include "Common.h"
#include "MatchList.h"
#include "Match.h"
#include "Stat.h"
#include <functional>
#include <map>
#include <algorithm>


// Match property extractor
#define PropExt std::function<StringV(Match)>

// Variant match list extractor (list of matches with a certain variant)
#define MatchVExt std::function<std::vector<Match>(MatchList, std::string)>


class StatList
{
public:

	/**
	 * @brief Construct an empty stats list
	*/
	StatList();
	

	/**
	 * @brief Construct a list of statistics
	 * @param matchList The full match list 
	 * @param propExt Extracts the property from a match
	 * @param ignore A list of variants to ignore
	 * @param cutoff Percentage cutoff used to exclude variants
	 * @param matchVExt Extract list of matches with variant from matchlist
	*/
	StatList(const MatchList& matchList, const PropExt& propExt, 
		const StringV& ignore, const double& cutoff,
		const MatchVExt& matchVExt);


	/**
	 * @return The underlying list
	*/
	std::vector<Stat> getStatList();

private:

	/**
	 * @brief The underlying data structure
	*/
	std::vector<Stat> statList;
};

