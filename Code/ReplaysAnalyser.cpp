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


// MAIN: Analyse replays
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
	// Note: Relies on matchlist being sorted by date beforehand
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

	// Create map of unique strings paired with how many there are
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
			if (statName == "Player" && (curS == "davo" || curS == "ANON"))
			{
				continue;
			}

			// Increment the count of the variant (or add a new key with a count of 1)
			itemVariants[curS]++;
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

	// Print heading and lines for each variant-count pair
	printColumns("%", statName, "Matches", "Date Range");
	for (VCPair curPair : itemVariantsV)
	{
		printVCPair(curPair, statName);
	}
}


// Helper: Print out a given variant-count pair
void ReplaysAnalyser::printVCPair(VCPair vcPair, string statName)
{
	// Calculate the percentage of matches with the variant
	int varCount = vcPair.second;
	double percentage = ((double)varCount / (double)matchNum) * 100;

	// If percentage significant:
	if (percentage > cutoff)
	{
		// Get variant value
		string varValue = vcPair.first;

		// Get date range for current property
		string dateRange = "";
		if (statName == "Version")
		{
			dateRange = getDateRangeForMatches(ml.getVersionMatches(varValue));
		}
		else if (statName == "Year")
		{
			dateRange = getDateRangeForMatches(ml.getYearMatches(varValue));
		}
		else if (statName == "Player")
		{
			dateRange = getDateRangeForMatches(ml.getPlayerMatches(varValue));
		}
		else if (statName == "Character")
		{
			dateRange = getDateRangeForMatches(ml.getCharMatches(varValue));
		}

		// Print statistics information
		printStatsLine(percentage, varValue, varCount, dateRange);
	}
}


// Helper: Get date range string for a given list of matches
string ReplaysAnalyser::getDateRangeForMatches(vector<Match> matchList)
{
	// Find oldest and newest matches
	auto dateRangePair = std::minmax_element(matchList.begin(), matchList.end(),
		[](Match m1, Match m2) {
			// Return 'greater' internal date
			return (m1.getDate().getYMD() < m2.getDate().getYMD());
		});

	// Extract date strings and format together
	string oldest = dateRangePair.first._Ptr->getDate().toString();
	string newest = dateRangePair.second._Ptr->getDate().toString();
	return format("{} - {}", oldest, newest);
}


// Helper: Print out statistics line
void ReplaysAnalyser::printStatsLine(double percentage, string curV, int freq, string dateRange)
{
	// Convert to strings
	string freqS = to_string(freq);
	string percentS = to_string(percentage).erase(4) + "%";

	// Print in certain way
	if (columnPrint)
	{
		// Print in columns
		printColumns(percentS, curV, freqS, dateRange);
	}
	else
	{
		// Print formatted
		print(format("{} = {} ({} matches) ({})", percentS, curV, freqS, dateRange));
	}
}


// Helper: Print out columns
void ReplaysAnalyser::printColumns(string c1, string c2, string c3, string c4)
{
	if (columnPrint)
	{
		cout
			<< std::left
			<< "\n"
			<< setw(10) << c1
			<< setw(15) << c2
			<< setw(10) << c3
			<< c4;
	}
}


// Helper: Print statistics heading line
void ReplaysAnalyser::printStatsHeading(string statName)
{
	printHeading(format("{} {}", statName, "Statistics"));
}


// Helper: Print heading line
void ReplaysAnalyser::printHeading(string statName)
{
	print(format("\n### {} ###", statName));
}


// Helper: Print settings update
void ReplaysAnalyser::printSettingsUpdate(string msg)
{
	// DISABLED, only enable when debugging
	// print(format("$$$ Settings Update: {}\n", msg));
}