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

// For sort
#include <algorithm>


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

	// Number of matches
	int matchNum;
	


	// ### Private methods
	// # Helpers
	std::string getReplayPath();
	void printColumns(std::string, std::string, std::string);
	void printStatsLine(double, std::string, int);
	void printSettingsUpdate(std::string);
	void printStatsHeading(std::string);
	void printDateStats();

	// # Main Statistics Method
	template <typename Property>
	void printFreqStats(std::string, std::function<Property(Match)>);
};

