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
	printFreqStats("Version",
		[](Match m) -> StringV {
			return StringV{ m.getVersion() };
		});

	// 3) Year stats
	printFreqStats("Year",
		[](Match m) -> StringV {
			return StringV{ to_string(m.getYear()) };
		});

	// 4) Player stats
	printFreqStats("Player",
		[](Match m) -> StringV {
			return m.getFighters().getPlayers();
		});

	// 5) Character stats
	printFreqStats("Character",
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
// func: Function that retrieves properties (String Vector)
void ReplaysAnalyser::printFreqStats(string statName, function<StringV(Match)> func)
{
	// Starting message
	printStatsHeading(statName);

	// # Create map of unique strings paired with how many there are
	map<string, int> itemVariants;

	// For each match
	vector<Match> matches = ml.getMatches();
	for (Match curMatch : matches)
	{
		// Extract string properties using the function given (e.g. player names)
		StringV curProps = func(curMatch);

		// For each string
		for (string curS : curProps)
		{
			// If calculating player stats and a special player is encountered, skip them
			if (contains(statName, "Player")
				&& (contains(curS, "davo") || contains(curS, "ANON")))
			{
				continue;
			}

			// If the string is already in the map
			if (itemVariants.contains(curS))
			{
				// Increment its count
				itemVariants[curS]++;
			}
			else
			{
				// Else if its not in the map, add it
				itemVariants[curS] = 1;
			}
		}
	}

	// Convert the map to a vector since maps cannot be sorted
	vector<VCPair> itemVariantsV(itemVariants.begin(), itemVariants.end());

	// Sort the variants, placing the highest count variants at the top
	sort(itemVariantsV.begin(), itemVariantsV.end(),
		[](const VCPair pair1, const VCPair pair2) {
			// Compare pairs by their counts
			return pair1.second > pair2.second;
		});

	// # Print out variant-count pairs
	// Print headings (if column mode on)
	printColumns("%", statName, "Matches");

	// For all pairs
	for (VCPair curPair : itemVariantsV)
	{
		// Extract count (of items for given variant)
		int count = curPair.second;

		// Calculate percentage
		// Note: Match count used as total as some matches have multiple items
		double percentage = ((double)count / (double)matchNum) * 100;

		// Print line from pair
		printStatsLine(percentage, curPair.first, count);
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