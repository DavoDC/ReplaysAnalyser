#pragma once

// ReplaysAnalyser.h
// Analyses replays by calculating statistics

// ### Headers
// Include common
#include "Common.h"

// Include needed headers
#include "MatchList.h"


// ### Libraries
// For function type
#include <functional>

// For set
#include <set>


// ### Macros
// Frequency (int) and Variant (string) type
#define FVPair std::pair<int, std::string>

// String set type
#define StringSet std::set<std::string>



// Declare ReplaysAnalyser class
class ReplaysAnalyser {

public:

	// Custom Constructor
	ReplaysAnalyser(double cutoff = 0.6, bool debugMode = false);


private:
	// ### Private fields
	// Debug Mode Toggle (uses sample data for faster tests)
	bool debugMode;

	// Percentage Cutoff Value
	double cutoff;

	// MatchList
	MatchList ml;

	


	// ### Private methods
	// # Other
	void analyse();
	std::string getReplayPath();

	// # Simple Statistics Helpers
	void printStatsLine(std::string);
	void printDateStats();

	// # Frequency Statistics Helpers
	template <typename Property>
	void printFreqStats(std::string, std::function<Property(Match)>);

	void printVariantAnalysis(StringSet, StringV);
	void printByPercentage(std::vector<FVPair>);
};

