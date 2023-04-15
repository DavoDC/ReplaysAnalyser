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

	// Constructor
	ReplaysAnalyser();

	// Analyse driver
	void analyse();

	// Settings
	void toggleSampleData();
    void setCutoff(double);
	void toggleColumnPrint();


private:
	// ### Private fields
	// Use Sample Data
	bool useSampleData;

	// Percentage Cutoff Value
	double cutoff;

	// Column Printing
	bool columnPrint;

	// MatchList
	MatchList ml;

	


	// ### Private methods
	// # General
	std::string getReplayPath();
	void printSettingsUpdate(std::string);

	// # Simple Statistics Helpers
	void printStatsLine(std::string);
	void printDateStats();

	// # Frequency Statistics Helpers
	template <typename Property>
	void printFreqStats(std::string, std::function<Property(Match)>);

	void printVariantAnalysis(StringSet, StringV);
	void printByPercentage(std::vector<FVPair>);
};

