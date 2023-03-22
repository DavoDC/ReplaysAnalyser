// ReplaysAnalyser.cpp : 
// This file contains the 'main' function. 
// Program execution begins and ends there.

// Header file
#include "ReplaysAnalyser.h"

// Libraries
#include <filesystem>

// Namespace mods
using namespace std;
namespace fs = filesystem;



// ### Global variables
// 
// ## Replay folder path
// # TEST VALUE
const string replayPath = "../Sample_Data";
// # TEST VALUE 2
//const string replayPath = "C:/Users/David/GitHubRepos/SSF2ReplaysCOPY";
// # ACTUAL VALUE
//'C:/Users/David/SSF2Replays'

// ## Match list
vector<Match> matches;


// Main func
int main()
{
	// Welcome message
	print("####### WELCOME TO REPLAYS ANALYSER #######", true);

	// Step 1 = Parse matches
	parseMatches();

	print("size: " + to_string(matches.size()));

	// TEST
	for (Match curM : matches)
	{
		print(curM.getDate().toString());
	}
	
	

	// END
	print("\n");
}



// Parse matches
void parseMatches()
{
	// For every path in the directory
	for (const auto& curPath : fs::recursive_directory_iterator(replayPath)) {

		// Convert current path to string
		string curPathS = curPath.path().generic_string();

		// If it is a replay path/file
		if (strstr(curPathS.c_str(), ".ssfrec")) {

			// Convert to Match and add to list
			matches.push_back(Match(curPathS));
		}
	}
}