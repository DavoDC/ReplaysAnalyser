// ReplaysAnalyser.cpp : 
// This file contains the 'main' function. 
// Program execution begins and ends there.

// Header file
#include "ReplaysAnalyser.h"

// Include needed header
#include "MatchList.h"

// Libraries
#include <set>
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
void printPercentageBreakdown(set<string> uniques, vector<string> all);
void printPercentageBreakdown(vector<Match> matchV, function<string(Match)> func);

//// TEST
//#include <functional>
//// Function that takes a pointer
//// to a function
//int invoke(int x, int y, function<int(int, int)> func)
//{
//	return func(x, y);
//}
//
//// Function that takes a pointer
//// to a function
//string invokeS(Match m, function<string(Match)> func)
//{
//	return func(m);
//}





// Main func
int main()
{
	// Welcome message
	print("####### WELCOME TO REPLAYS ANALYSER #######");

	// Parse matches into list of matches
	MatchList ml = MatchList(replayPath);
	int matchCount = ml.getSize();
	print("\nParsed " + ml.getSizeS() + " matches!");

	// Sort by date
	ml.sortByDate();

	// Print out info
	//ml.printInfo();

	// ### Version Stats
	print("\n### Version Stats ###");
	printPercentageBreakdown(ml.getMatches(), [](Match m) -> string {
		return m.getVersion();
		});

	/*;
	set<string> uniqVersions;
	vector<string> allVersions;
	for (Match curMatch : ml.getMatches())
	{
		string curVersion = curMatch.getVersion();
		uniqVersions.insert(curVersion);
		allVersions.push_back(curVersion);
	}
	printPercentageBreakdown(uniqVersions, allVersions);*/


	
	// ### Year Stats
	print("\n### Year Stats ###");
	printPercentageBreakdown(ml.getMatches(), [](Match m) -> string {
		return to_string(m.getYear());
		});
	/*
	set<string> years;
	vector<string> allYears;
	for (Match curMatch : ml.getMatches())
	{
		string curVersion = to_string(curMatch.getYear());
		years.insert(curVersion);
		allYears.push_back(curVersion);
	}
	printPercentageBreakdown(years, allYears);*/



	//Match m = ml.getMatches()[0];
	
	

	// Perform Addition
	/*print("Addition of 20 and 10 is ");
	int k = invoke(20, 10,
		[](int x,
			int y) -> int {
				return x + y;
		});
	print(to_string(k), true);


	Match m = ml.getMatches()[0];
	print("The version of this match object is ");
	string s = invokeS(m,
		[](Match m) -> string {
				return m.getVersion();
		});
	print(s);*/


	

	// END
	print("\n");
}




void printPercentageBreakdown(vector<Match> matchV, function<string(Match)> func)
{
	// Unique items
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

	// Pass to helper
	printPercentageBreakdown(variants, all);
}



// Print each version and percentage
// uniques: A set containing each variant
// all: All the items
void printPercentageBreakdown(set<string> uniques, vector<string> all)
{
	// Total items
	int total = int(all.size());

	// For each variant
	for (string curV : uniques)
	{
		// Find out how many instances of this variant are present
		int freq = int(count(all.begin(), all.end(), curV));
		string freqS = to_string(freq);

		// Calculate a percentage out of the total items
		int percentage = int(round(((double)freq / (double) total) * 100));
		string percentageS = to_string(percentage);

		// Final
		print(format("{} = {} matches ({}%)", curV, freqS, percentageS));
	}
}
