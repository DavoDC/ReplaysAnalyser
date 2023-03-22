// ReplaysAnalyser.cpp : 
// This file contains the 'main' function. 
// Program execution begins and ends there.

// Header files
#include "Common.h"
#include "Match.h"

// Namespace mods
using namespace std;
namespace fs = filesystem;

// Global variables
// Replay folder path
// - AT TESTING VALUE
// - Actual: 'C:/Users/David/SSF2Replays'
const std::string replayPath = "../Sample_Data";

// Main func
int main()
{
	// Welcome message
	print("####### WELCOME TO REPLAYS ANALYSER #######", true);

	//// For every path in the directory
	for (const auto& curPath : fs::recursive_directory_iterator(replayPath)) {

		// Convert current path to string
		string curPathS = curPath.path().generic_string();

		// If it is a replay path/file
		if (strstr(curPathS.c_str(), ".ssfrec")) {

			// Create Match from path line
			Match m = Match(curPathS);

			// Print 
			print(curPathS);

			// STOP, TESTING
			break;
		}
	}




	// END
	print("\n");
}

// Helper function for printing
void print(string s, bool useEndl)
{
	cout << "\n" << s;
	if (useEndl) {
		cout << endl;
	}
}