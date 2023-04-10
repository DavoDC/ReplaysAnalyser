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


// Main func
int main()
{
	// Get starting timepoint
	auto start = chrono::high_resolution_clock::now();


	// ### Analyse replays by creating analyser
	// Default
	ReplaysAnalyser ra;

	// Use lower cutoff
	//ReplaysAnalyser ra(0.2, false);

	// Use sample data for fast testing
	//ReplaysAnalyser ra (0.6, true); 


	// Get ending timepoint
	auto stop = chrono::high_resolution_clock::now();

	// Calculate duration and format
	auto rawDur = duration_cast<chrono::milliseconds>(stop - start);
	double durDoub = double(rawDur.count()) / 1000.0;
	string durationS = to_string(durDoub).erase(5);

	// Notify
	print(format("\nTime taken: {} seconds", durationS));

	// END
	print("\n");
}