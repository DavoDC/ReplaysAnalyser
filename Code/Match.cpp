// Match.cpp : 
// Defines Match class

// Header file
#include "Match.h"

// Namespace mods
using namespace std;

// Libraries
#include <algorithm>

// Helper function
string removeChar(string s, char c) {
	s.erase(std::remove(s.begin(), s.end(), c), s.end());
	return s;
}

// Construct a match from a replay name
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

	// Extract player-character pairs
	string rawPCpairs = replayParts.back();

	// Remove extension
	string ext = ".ssfrec";
	size_t start_pos = rawPCpairs.find(ext);
	rawPCpairs.replace(start_pos, ext.length(), "");

	// Split into individual pairs
	vector<string> pairs = split(rawPCpairs, " vs ");

	// For every pair string
	for (string curPairS : pairs) {

		// Split into player and character
		vector<string> curPairParts = split(curPairS, " ");

		// Extract player
		string player = curPairParts.front();

		// Extract character
		string character = curPairParts.back();
		character = removeChar(character, '(');
		character = removeChar(character, ')');

        // # 3rd FIELD
		// Create pair object
		pair<string, string> pcPair(player, character);

		// Add to pair vector
		pcPairs.push_back(pcPair);
	}
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

