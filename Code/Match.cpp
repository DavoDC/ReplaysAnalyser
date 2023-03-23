// Match.cpp : 
// Defines Match class

// Header file
#include "Match.h"

// Namespace mods
using namespace std;


// Construct a match from a raw replay name
Match::Match(string replayName)
{
	// Split replay name into parts
	vector<string> pathParts = split(replayName, "/");

	// # 1st FIELD
	// Extract and save version (2nd last part)
	version = pathParts[pathParts.size() - 2];

	// Extract replay name and split into parts
	string filename = pathParts.back();
	vector<string> replayParts = split(filename, " - ");

	// # 2nd FIELD
	// Extract date, convert and save
	date = ReplayDate(replayParts.front());

	// # 3rd FIELD
	pcPairs = StringPairs(replayParts.back());
}



// Get a string representation of the match (one line)
string Match::toString()
{
	string result = date.toString();
	result += ", V:" + version;
	result += ", " + pcPairs.toString();
	return result;
}




// Getters
string Match::getVersion()
{
	return version;
}

ReplayDate Match::getDate()
{
	return date;
}

StringPairs Match::getPCPairs()
{
	return pcPairs;
}