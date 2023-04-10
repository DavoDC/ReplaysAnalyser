// ReplaysAnalyser.cpp : 
// Defines ReplaysAnalyser class

// Include header file
#include "ReplaysAnalyser.h"

// Namespace mods
using namespace std;


// Constructor
ReplaysAnalyser::ReplaysAnalyser(double cutoff, bool debugMode)
{
	// Welcome message
	print("####### WELCOME TO REPLAYS ANALYSER #######");

	// Set variables
	this->debugMode = debugMode;
	this->cutoff = cutoff;

	// Parse matches in replay path
	ml = MatchList(getReplayPath());

	// Notify
	print("\nParsed " + ml.getSizeS() + " matches!");

	// Analyse replays
	analyse();
}



// Helper: Get replay path
string ReplaysAnalyser::getReplayPath()
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
	}
	else {
		print("\nError reading %USERNAME% !!!");
	}

	// Add username and folder
	replayPath += username + string("/SSF2Replays");

	// Return replay path
	return replayPath;
}




// Analyse replays
void ReplaysAnalyser::analyse()
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
	printFreqStats<StringV>("Player",
		[](Match m) -> StringV {
			return m.getFighters().getPlayers();
		});

	// 5) Character stats
	printFreqStats<StringV>("Character",
		[](Match m) -> StringV {
			return m.getFighters().getChars();
		});
}


// Helper: Print statistics starting line
void ReplaysAnalyser::printStatsLine(string statName)
{
	print(format("\n### {} Statistics ###", statName));
}


// Helper: Print date statistics
void ReplaysAnalyser::printDateStats()
{
	// Header
	printStatsLine("Date");

	// Current Date
	auto now = chrono::system_clock::now();
	DateM ymd{ chrono::floor<chrono::days>(now) };
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
void ReplaysAnalyser::printFreqStats(string statName, function<Property(Match)> func)
{
	// Starting message
	printStatsLine(statName);

	// A set containing each variant (unique items)
	StringSet variants;

	// All items
	StringV all;

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
		else if constexpr (is_same_v<Property, StringV>) {
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
void ReplaysAnalyser::printVariantAnalysis(StringSet variants, StringV all)
{
	// Frequency-variant pairs
	vector<FVPair> fvPairs;

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
void ReplaysAnalyser::printByPercentage(vector<FVPair> fvPairs)
{
	// Sort by freq
	sort(fvPairs.begin(), fvPairs.end(),
		[](FVPair p1, FVPair p2) {

			// Return 'greater' pair
			return (p1.first > p2.first);
		});

	// Total items
	// (Use number of matches as total as some matches have multiple items)
	int total = ml.getSize();

	// For all pairs
	for (FVPair curPair : fvPairs)
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

