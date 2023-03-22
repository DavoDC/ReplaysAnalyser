// Match.cpp : 
// Defines Match class

// Header file
#include "Match.h"

// Namespace mods
using namespace std;

// Construct a match from a replay name
Match::Match(string replayName)
{
	// Split replay name into parts
	vector<string> pathParts = split(replayName, "/");

	// Extract and save version (2nd last part)
	version = pathParts[pathParts.size() - 2];

	// Extract replay name and split into parts
	string filename = pathParts.back();
	vector<string> replayParts = split(filename, " - ");

	// Extract date, convert and save
	date = ReplayDate(replayParts.front());

	// TEST
	//string yr = to_string(int(date.getDate().year()));
	//print("year: " + yr);

	// Extract player-character pairs
	string rawPCpairs = replayParts.back();
	//print(string("raw pairs: ") + rawPCpairs);

}