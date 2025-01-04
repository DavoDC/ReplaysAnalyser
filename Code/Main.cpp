// Main.cpp
// (Has no header file for self)
#include "Common.h"
#include "ReplaysAnalyser.h"
#include <chrono>

// Namespace mods
using namespace std;


/**
 * @brief Print out the time passed (in seconds) since a given start time
*/
void printTimeTaken(const auto& startTime);


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
	//ra.togglePrintingReviewMessages();
	//ra.toggleOnlineMatchesOnly();
	//ra.useSampleData();
	//ra.setPlayerCutoff(0);
	
	// Run analysis
	ra.analyse();

	//ra.printFixedDates();

	// # Print time taken and finish
	printTimeTaken(start);
	print("\n");
}


void printTimeTaken(const auto& startTime)
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