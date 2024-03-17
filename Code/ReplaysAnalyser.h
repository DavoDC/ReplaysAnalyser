#pragma once

// ReplaysAnalyser.h
// Analyses replays by calculating statistics

// ### Headers
// Include common
#include "Common.h"

// Helper classes
#include "MatchList.h"
#include "StatPrinter.h"
#include "StatList.h"


// Declare ReplaysAnalyser class
class ReplaysAnalyser {

public:

	// Constructor
	ReplaysAnalyser();

	// Settings
	void toggleSampleData();
	void setCutoff(double);

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
};

