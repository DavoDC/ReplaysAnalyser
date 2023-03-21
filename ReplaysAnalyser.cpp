// ReplaysAnalyser.cpp : 
// This file contains the 'main' function. 
// Program execution begins and ends there.

#include <string>
#include <iostream>
#include <filesystem>

using namespace std;

int main()
{
	// Start message 
	cout << "\n####### WELCOME TO REPLAYS ANALYSER \n";

	// Set path to read from
	string path = "SAMPLE_DATA";

	// For every path in the directory
	for (const auto& curPath : filesystem::recursive_directory_iterator(path)) {

		// Convert to string
		string curPathS = curPath.path().generic_string();

		// If doesn't have dot/ext, add space  (Separates folders)
		if (!strstr(curPathS.c_str(), ".")) {
			cout << "\n" << endl;
		}

		// Print 
		cout << curPathS << endl;
	}

}