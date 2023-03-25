// ReplaysAnalyser.cpp : 
// This file contains the 'main' function. 
// Program execution begins and ends there.

// Header file
#include "ReplaysAnalyser.h"

// Include needed header
#include "MatchList.h"

// Namespace mods
using namespace std;

// ### Global variables

// ## Replay folder path
// # TEST VALUE
const string replayPath = "../Sample_Data";
// # TEST VALUE 2
//const string replayPath = "C:/Users/David/GitHubRepos/SSF2ReplaysCOPY";
// # ACTUAL VALUE
//'C:/Users/David/SSF2Replays'



// Main func
int main()
{
	// Welcome message
	print("####### WELCOME TO REPLAYS ANALYSER #######", true);

	// Parse matches into list of matches
	MatchList ml = MatchList(replayPath);
	print("Parsed " + ml.getSizeS() + " matches!");

	//ml.printInfo();


	// END
	print("\n");
}


