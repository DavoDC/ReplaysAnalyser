// Match.cpp : 
// Defines Match class

// Header file
#include "Match.h"

// Namespace mods
using namespace std;


// Construct a match from a raw replay path
// e.g. ../Sample_Data/1.3.1.1/2021-08-24 11.44 AM - 2021-08-24 11.44 AM......." 
Match::Match(string replayPath)
{
	// Split replay name into parts
	// e.g
	// ".."
	// "Sample_Data"
	// "1.3.1.1"
	// "2021-08-24 11.44 AM - VersusOnline - davo1776 (Wario)......."
	vector<string> pathParts = split(replayPath, "/");
	// NOTE: Check disabled since path length/structure can vary

	// # INIT 1st FIELD
	// Extract and save version (2nd last part)
	// e.g. 1.3.1.1
	version = pathParts[pathParts.size() - 2];

	// If doesn't have length 7
	if (version.length() != 7)
	{
		// Notify
		print("WARNING: Unusual version string detected!");
		print("Version: " + version);
	}

	// Extract replay name (last part)
	// e.g. 2021-08-24 11.44 AM - VersusOnline - davo1776 (Wario).......
	string filename = pathParts.back();


	// Split replay name into 3 parts
	// e.g
	// "2021-08-24 11.44 AM" - 
	// "VersusOnline"
	// "davo1776 (Wario) vs HexxaWyn (Naruto) ...."
	vector<string> replayParts = split(filename, " - ", 3);

	// # INIT 2nd FIELD
	// Extract date from first string
	// e.g. "2021-08-24 11.44 AM"
	date = ReplayDate(replayParts.front());

	// # INIT 3rd FIELD
	// Extract player-character pairs from last string
	// e.g. "davo1776 (Wario) vs HexxaWyn (Naruto) ...."
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