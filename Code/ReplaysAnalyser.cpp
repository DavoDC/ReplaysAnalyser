// ReplaysAnalyser.cpp : 
// This file contains the 'main' function. 
// Program execution begins and ends there.

// No header file for self

// Include needed headers
#include "Common.h"
#include "MatchList.h"

// ### Libraries
// # For set
#include <set>
// # For function type
#include <functional>
// # For timing
#include <chrono>


// Namespace mods
using namespace std;



// ### Global variables
// ## Replay folder path
// # TEST VALUE
//const string replayPath = "../Sample_Data";
// # TEST VALUE 2
const string replayPath = "C:/Users/David/GitHubRepos/SSF2ReplaysCOPY";
// # ACTUAL VALUE
//'C:/Users/David/SSF2Replays'





// Class definition and declaration in one 
// (as a reminder that this can be done)
class ReplaysAnalyser {

private:
	// ### Private fields
	// # #Matchlist
	MatchList ml;

	// ### Private methods
	// Helper: Print frequency statistics for a given STRING property
	// statName: Name for this group of statistics
	// func: Function that retrieves property
	void printFreqStats(string statName, function<string(Match)> func)
	{
		// Starting message
		printStatsLine(statName);

		// A set containing each variant (unique items)
		set<string> variants;

		// All items
		stringV all;

		// For all matches
		for (Match curMatch : ml.getMatches())
		{
			// Extract some info
			string curItem = func(curMatch);

			// Add to both lists
			variants.insert(curItem);
			all.push_back(curItem);
		}

		// Print variant analysis
		printVariantAnalysis(variants, all);
	}

	// Helper: Print frequency statistics for a given STRING VECTOR property
	// statName: Name for this group of statistics
	// func: Function that retrieves property (STRING VECTOR)
	void printFreqStats(string statName, function<stringV(Match)> func)
	{
		// Starting message
		printStatsLine(statName);

		// A set containing each variant (unique items)
		set<string> variants;

		// All items
		stringV all;

		// For all matches
		for (Match curMatch : ml.getMatches())
		{
			// Extract vector info
			stringV curList = func(curMatch);

			// Add all items to both lists
			for (string curItem : curList)
			{
				variants.insert(curItem);
				all.push_back(curItem);
			}
		}

		// Print variant analysis
		printVariantAnalysis(variants, all);
	}

	// Helper: Print analysis of variants
	// variants: Set of unique items
	// all: Vector of all items
	void printVariantAnalysis(set<string> variants, stringV all)
	{
		// Total items
		// (Use number of matches as total as some matches have multiple items)
		int total = ml.getSize();

		// For each variant
		for (string curV : variants)
		{
			// Special: Skip me
			if (contains(curV, "davo"))
			{
				break;
			}

			// Find out how many instances of this variant are present
			int freq = int(count(all.begin(), all.end(), curV));
			string freqS = to_string(freq);

			// Calculate as a percentage out of the total items
			double percentage = ((double)freq / (double)total) * 100;
			string percentageS = to_string(percentage).erase(4);
		
			// If percentage significant
			if (percentage > 0.9)
			{
				// Format and print
				print(format("{} = {} matches ({}%)", curV, freqS, percentageS));
			}
			
		}
	}

	// Helper: Print statistics starting line
	void printStatsLine(string statName)
	{
		print(format("\n### {} Statistics ###", statName));
	}

public:

	// Constructor
	ReplaysAnalyser()
	{
		// Welcome message
		print("####### WELCOME TO REPLAYS ANALYSER #######");

		// Parse matches and notify
		ml = MatchList(replayPath);
		print("\nParsed " + ml.getSizeS() + " matches!");

		// Sort by date
		ml.sortByDate();

		// Print out info
		// ml.printInfo();
	}


	// Analyse replays
	void analyse()
	{
		// 1) Version stats
		printFreqStats("Version",
			[](Match m) -> string {
				return m.getVersion();
			});

		// 2) Year stats
		printFreqStats("Year",
			[](Match m) -> string {
				return to_string(m.getYear());
			});

		// 3) Player stats
		printFreqStats("Player",
			[](Match m) -> stringV {
				return m.getFighters().getPlayers();
			});

		// 4) Character stats
		printFreqStats("Character",
			[](Match m) -> stringV {
				return m.getFighters().getChars();
			});
	}

};










// Main func
int main()
{
	// Get starting timepoint
	auto start = chrono::high_resolution_clock::now();

	// Create replays analyser
	ReplaysAnalyser ra;

	// Analyse replays
	ra.analyse();

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