// Main.cpp : 
// This file contains the 'main' function. 
// Program execution begins and ends there.

// ### Libraries
// # For timing
#include <chrono>

// No header file for self

// Include needed headers
#include "Common.h"
#include "ReplaysAnalyser.h"

// Namespace mods
using namespace std;

// Function Declaration
void printTimeTaken(auto);


// Main function
int main()
{
	// # Get starting timepoint
	auto start = chrono::high_resolution_clock::now();

	// # Create analyser
	ReplaysAnalyser ra;

	// My settings
	ra.addIgnoredPlayer("davo");

	// Settings for Spi's replays
	//ra.setCustomLocalRepoFolder("Spi-SSF2Replays");
	//ra.setOfflinePlayerAliases("Spi", AliasHandler::ANON);
	//ra.addIgnoredPlayer("Spi");

	// Other settings
	//ra.toggleOnlineMatchesOnly();
	//ra.useSampleData();
	//ra.setPlayerCutoff(0);
	
	// Run analysis
	ra.analyse();

	// # Print time taken and finish
	printTimeTaken(start);
	print("\n");
}


// Helper: Print time taken base
void printTimeTaken(auto startTime)
{
	// Get ending timepoint
	auto stopTime = chrono::high_resolution_clock::now();

	// Calculate duration
	auto rawDur = stopTime - startTime;
	auto dur = duration_cast<chrono::milliseconds>(rawDur);
	double durDoub = double(dur.count()) / 1000.0;
	
	// Format and notify
	string durationS = to_string(durDoub).erase(5);
	print(format("\nTime taken: {} seconds", durationS));
}