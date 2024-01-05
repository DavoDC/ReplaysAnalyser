// ReplaysAnalyser.cpp : 
// Defines ReplaysAnalyser class

// Include header file
#include "ReplaysAnalyser.h"

// Namespace mods
using namespace std;


// Constructor
ReplaysAnalyser::ReplaysAnalyser()
{
	// Set variables to default values
	this->useSampleData = false;
	this->cutoff = 0.6;
	this->columnPrint = true;
	this->matchNum = 0;

	// Note: MatchList not here but uses default constr.
}


// ### Setters
// Toggle sample data
void ReplaysAnalyser::toggleSampleData()
{
	printSettingsUpdate("Sample Data");
	useSampleData = !useSampleData;
}

// Set cut off
// newCutoff = Percentage value (e.g. 5.0 = 5%)
void ReplaysAnalyser::setCutoff(double newCutoff)
{
	printSettingsUpdate("Cutoff");
	cutoff = newCutoff;
}

// Toggle columing printing
void ReplaysAnalyser::toggleColumnPrint()
{
	printSettingsUpdate("Column Printing");
	columnPrint = !columnPrint;
}





// Analyse replays
void ReplaysAnalyser::analyse()
{
	// Welcome message
	print("####### WELCOME TO REPLAYS ANALYSER #######");

	// Parse replays in path and notify
	ml = MatchList(getReplayPath());
	print("\nParsed " + ml.getSizeS() + " matches!");

	// Save total matches
	matchNum = ml.getSize();

	// ### Print stats
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



// Helper: Get replay path
string ReplaysAnalyser::getReplayPath()
{
	// If sample data usage on
	if (useSampleData)
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



// Helper: Print date statistics
void ReplaysAnalyser::printDateStats()
{
	// Header
	printStatsHeading("Date");

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
	printStatsHeading(statName);


	// # Holders
	// A set containing each variant (unique items)
	StringSet variants;

	// All items
	StringV all;


	// # Get variants and items
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


	// # Generate frequency-variant pairs
	// Holder
	vector<FVPair> fvPairs;

	// For each variant
	for (string curV : variants)
	{
		// If a special player
		if (contains(curV, "davo") || contains(curV, "ANON"))
		{
			// Skip
			continue;
		}

		// Find out how many instances of this variant are present
		int freq = int(count(all.begin(), all.end(), curV));

		// Add pair to list
		fvPairs.push_back(make_pair(freq, curV));
	}


	// # Sort freq-var pairs by frequency
	sort(fvPairs.begin(), fvPairs.end(),
		[](FVPair p1, FVPair p2) {

			// Return pair with greater frequency
			return (p1.first > p2.first);
		});


	// # Print freq-var pairs
	// Print headings (if column mode on)
	printColumns("%", statName, "Matches");

	// For all pairs
	for (FVPair curPair : fvPairs)
	{
		// Extract frequency
		int freq = curPair.first;

		// Calculate percentage
		// Note: Match count used as total as some matches have multiple items
		double percentage = ((double) freq / (double) matchNum) * 100;

		// Extract 
		string curV = curPair.second;

		// Print line for pair
		printStatsLine(percentage, curV, freq);
	}
}



// Helper: Print freq-variant pairs
// statName: Name for this group of statistics
// fvPairs: Frequency-variant pairs
void ReplaysAnalyser::printStatsLine(double percentage, string curV, int freq)
{
	// Convert to strings
	string freqS = to_string(freq);
	string percentS = to_string(percentage).erase(4) + "%";

	// If percentage significant
	if (percentage > cutoff)
	{
		// Print in certain way
		if (columnPrint)
		{
			// Print in columns
			printColumns(percentS, curV, freqS);
		}
		else
		{
			// Print formatted
			print(format("{} = {} ({} matches)", percentS, curV, freqS));
		}
	}
}




// Helper: Print three columns
void ReplaysAnalyser::printColumns(string c1, string c2, string c3)
{
	if (columnPrint)
	{
		cout
			<< std::left
			<< "\n"
			<< setw(10) << c1
			<< setw(15) << c2
			<< c3;
	}
}




// Helper: Print statistics heading line
void ReplaysAnalyser::printStatsHeading(string statName)
{
	print(format("\n### {} Statistics ###", statName));
}


// Helper: Print settings update
void ReplaysAnalyser::printSettingsUpdate(string msg)
{
	// DISABLED, only enable when debugging
	// print(format("$$$ Settings Update: {}\n", msg));
}