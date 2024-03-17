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

// For sort
#include <algorithm>

// For map
#include <map>


// ### Macros
// Variant-Count pair
#define VCPair std::pair<std::string, int>


// Declare ReplaysAnalyser class
class ReplaysAnalyser {

public:

	// Constructor
	ReplaysAnalyser();

	// Settings
	void toggleSampleData();
	void setCutoff(double);
	void toggleColumnPrint();

	// Main function
	void analyse();


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
	void printColumns(std::string, std::string, std::string, std::string);
	void printStatsLine(double, std::string, int, std::string);
	void printSettingsUpdate(std::string);
	void printVCPair(VCPair, std::string);
	void printStatsHeading(std::string);
	void printHeading(std::string);
	void printDateStats();

	// # Main Statistics Method
	void printFreqStats(std::string, std::function<StringV(Match)>);
};

