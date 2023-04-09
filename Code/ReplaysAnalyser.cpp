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
// # Toggle debug mode (uses sample data for faster tests)
const bool debugMode = false;
//const bool debugMode = true;
// # Percentage cutoff value (mostly arbitrary)
const double cutoff = 0.6;
//const double cutoff = 0.2;





// Class definition and declaration in one 
// (as a reminder that this can be done)
class ReplaysAnalyser {

private:
	// ### Private fields
	// # #Matchlist
	MatchList ml;

	// ### Private methods

	// Helper: Print statistics starting line
	void printStatsLine(string statName)
	{
		print(format("\n### {} Statistics ###", statName));
	}

	// Helper: Print date statistics
	void printDateStats()
	{
		// Header
		printStatsLine("Date");

		// Current Date
		auto now = std::chrono::system_clock::now();
		DateM ymd{ std::chrono::floor<std::chrono::days>(now) };
		print("Current Date: " + Date(ymd).toString());

		// Date Range
		string oldest = ml.getMatches().front().getDate().toString();
		string newest = ml.getMatches().back().getDate().toString();
		print(format("Date Range: {} - {}  (Oldest to Newest)", oldest, newest));
	}


	// Helper: Print frequency statistics for a given property
	// statName: Name for this group of statistics
	// func: Function that retrieves property (String or String Vector)
	template <typename Property>
	void printFreqStats(string statName, function<Property(Match)> func)
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
			// Extract property info
			Property curProp = func(curMatch);

			// If type is string
			if constexpr (is_same_v<Property, string>) {

				// Simply add to both
				variants.insert(curProp);
				all.push_back(curProp);
			}
			else if constexpr (is_same_v<Property, stringV>) {
				// Else if type is string vector:
				// Iterate over all strings in vector
				for (string curItem : curProp) {
					
					// Add to both
					variants.insert(curItem);
					all.push_back(curItem);
				}
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
		// Frequency-variant pairs
		vector<pair<int, string>> fvPairs;

		// For each variant
		for (string curV : variants)
		{
			// Special players to skip
			if (contains(curV, "davo") || contains(curV, "ANON"))
			{
				continue;
			}

			// Find out how many instances of this variant are present
			int freq = int(count(all.begin(), all.end(), curV));

			// Add to list
			fvPairs.push_back(make_pair(freq, curV));
		}

		// Print percentages
		printByPercentage(fvPairs);
	}

	// Helper: Print sorted percentage breakdown of freq-variant pairs
	// fvPairs: Frequency-variant pairs
	void printByPercentage(vector<pair<int, string>> fvPairs)
	{
		// Sort by freq
		sort(fvPairs.begin(), fvPairs.end(),
			[](pair<int, string> p1, pair<int, string> p2) {

				// Return 'greater' pair
				return (p1.first > p2.first);
			});

		// Total items
		// (Use number of matches as total as some matches have multiple items)
		int total = ml.getSize();

		// For all pairs
		for (pair<int, string> curPair : fvPairs)
		{
			// Get percentage out of the total items
			int freq = curPair.first;
			double percentage = ((double)freq / (double)total) * 100;
			string percentS = to_string(percentage).erase(4);

			// Get variant value
			string curV = curPair.second;

			// Get frequency as a string
			string freqS = to_string(freq);

			// If percentage significant
			if (percentage > cutoff)
			{
				// Format and print
				print(format("{}% = {} ({} matches)", percentS, curV, freqS));
			}
		}
	}

	// Helper: Get replay path
	string getReplayPath()
	{
		// If debug mode on
		if (debugMode)
		{
			// Use sample data
			return string("../Sample_Data");
		}
		
		// Holder
		string replayPath = string("C:/Users/");

		// Get username from environment variable
		string username = "David";
		char* buf = nullptr;
		size_t sz = 0;
		if (_dupenv_s(&buf, &sz, "USERNAME") == 0 && buf != nullptr) {
			username = string(buf);
			free(buf);
		} else {
			print("\nError reading %USERNAME% !!!");
		}

		// Add username and folder
		replayPath += username + string("/SSF2Replays");

		// Return replay path
		return replayPath;
	}

	


public:

	// Constructor
	ReplaysAnalyser()
	{
		// Welcome message
		print("####### WELCOME TO REPLAYS ANALYSER #######");

		// Parse matches and notify
		ml = MatchList(getReplayPath());
		print("\nParsed " + ml.getSizeS() + " matches!");

		// Sort by date
		ml.sortByDate();
	}


	// Analyse replays
	void analyse()
	{
		// 1) Date stats
		printDateStats();

		// 2) Version stats
		printFreqStats<string>("Version",
			[](Match m) -> string {
				return m.getVersion();
			});

		// 3) Year stats
		printFreqStats<string>("Year",
			[](Match m) -> string {
				return to_string(m.getYear());
			});

		// 4) Player stats
		printFreqStats<stringV>("Player",
			[](Match m) -> stringV {
				return m.getFighters().getPlayers();
			});

		// 5) Character stats
		printFreqStats<stringV>("Character",
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