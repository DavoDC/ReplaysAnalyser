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

	// Setting functions
	void toggleSampleData();

	// Main function
	void analyse();

private:
	// ### Private fields
	
	// Sample data toggle
	bool useSampleData;


	// ### Private methods
	std::string getReplayPath();
};

