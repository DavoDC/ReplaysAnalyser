// ReplaysAnalyser.cpp : 
// This file contains the 'main' function. 
// Program execution begins and ends there.

// Header file
#include "ReplaysAnalyser.h"

// Include needed header
#include "MatchList.h"

// ### Libraries
// # For set
#include <set>
// # For function type
#include <functional>

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


// Declarations
void printFreqStats(vector<Match> matchV, function<string(Match)> func);




// Main func
int main()
{
	// Welcome message
	print("####### WELCOME TO REPLAYS ANALYSER #######");

	// Parse matches into list of matches
	MatchList ml = MatchList(replayPath);
	print("\nParsed " + ml.getSizeS() + " matches!");

	// Sort by date
	ml.sortByDate();

	// Print out info
	//ml.printInfo();

	// ### Version Stats
	print("\n### Version Stats ###");
	printFreqStats(ml.getMatches(), [](Match m) -> string {
		return m.getVersion();
		});


	// ### Year Stats
	print("\n### Year Stats ###");
	printFreqStats(ml.getMatches(), [](Match m) -> string {
		return to_string(m.getYear());
		});

	// END
	print("\n");
}





// Print frequency statistics for a given property
// matchV: List of matches
// func: Function that retrieves property
void printFreqStats(vector<Match> matchV, function<string(Match)> func)
{
	// A set containing each variant (unique items)
	set<string> variants;

	// All items
	vector<string> all;

	// For all matches
	for (Match curMatch : matchV)
	{
		// Extract some info
		string curItem = func(curMatch);

		// Add to both lists
		variants.insert(curItem);
		all.push_back(curItem);
	}

	// Total items
	int total = int(all.size());

	// For each variant
	for (string curV : variants)
	{
		// Find out how many instances of this variant are present
		int freq = int(count(all.begin(), all.end(), curV));
		string freqS = to_string(freq);

		// Calculate as a percentage out of the total items
		int percentage = int(round(((double)freq / (double)total) * 100));
		string percentageS = to_string(percentage);

		// Format nicely
		print(format("{} = {} matches ({}%)", curV, freqS, percentageS));
	}
}
