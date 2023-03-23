// StringPairs.cpp : 
// Defines StringPairs class

// Header file
#include "StringPairs.h"

// Namespace mods
using namespace std;

// Global constant - pair separator
const string pairSep = "###$###";


// Default Constructor
StringPairs::StringPairs()
{
	pairs = PairsM();
}


// Define StringPairs class
StringPairs::StringPairs(string rawPCpairs)
{
	// Remove extension
	replaceAll(rawPCpairs, ".ssfrec", "");

	// Split into individual pairs
	vector<string> pairs = split(rawPCpairs, " vs ");

	// For every pair string
	for (string curPairS : pairs) {

		// Convert to pair and add
		addPair(curPairS);
	}
}



// Helper function for adding pairs
void StringPairs::addPair(string rawPairS)
{
	// Add different separator than white space
	// (Because individual components have spaces as well)
	replaceAll(rawPairS, " (", pairSep);

	// Remove extra bracket at end
	replaceAll(rawPairS, ")", "");
	
	// Split into player and character
	vector<string> curPairParts = split(rawPairS, pairSep);

	// If split didn't work
	if (curPairParts.size() == 1)
	{
		// If not, notify
		print("WARNING: Major player-character split issue");
		print("RPS was: " + rawPairS, true);
	}
	
	// Extract 1st string, the player, and remove whitespace
	string player = curPairParts[0];
	replaceAll(player, " ", "");

	// Special: Replace my usernames with just 'davo'
	replaceAll(player, "DavoDC", "davo");
	replaceAll(player, "davo1776", "davo");

	// Extract 2nd string, the character, and remove whitespace
	string character = curPairParts[1];
	replaceAll(character, " ", "");
	
	// Create pair object
	PairM pcPair(player, character);

	// Add to pair vector
	pairs.push_back(pcPair);
}



// Get string representation
string StringPairs::toString()
{
	// Holder
	string result = "";

	// Get number of pairs
	int pLen = int(pairs.size());
	
	// Counter;
	int count = 0;

	// For every pair
	for (PairM curPair : pairs)
	{
		// Add player
		result += curPair.first;

		// Add character in brackets
		result += "(" + curPair.second + ")";

		// Add to counter
		count++;

		// Add separator, except on last pair
		if (count != pLen)
		{
			result += ", ";
		}
	}

	return result;
}