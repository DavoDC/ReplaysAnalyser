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


// Construct object from raw pairs
// e.g. "davo1776 (Wario) vs HexxaWyn (Naruto) 
// vs FakeNews (Falco) vs x77starboy (Naruto).ssfrec"
StringPairs::StringPairs(string rawPCpairs)
{
	// Remove extension
	replaceAll(rawPCpairs, ".ssfrec", "");

	// Split into individual pairs
	// e.g.
	// "davo1776 (Wario)"
	// "HexxaWyn (Naruto)"
	// "FakeNews (Falco)"
	// "x77starboy (Naruto)"
	vector<string> pairs = split(rawPCpairs, " vs ");

	// If there are not 2, 3 or 4 fighters
	int pLen = pairs.size();
	if (!(pLen >= 2 && pLen <= 4))
	{
		print("WARNING: Unusual number of fighters detected");
		print("Fighters: " + to_string(pLen));
	}

	// For every pair string
	for (string curPairS : pairs) {

		// Convert to pair and add
		addPair(curPairS);
	}
}



// Helper function that creates a pair from a given string
// e.g. "davo1776 (Wario)"
void StringPairs::addPair(string rawPairS)
{
	// Add different separator than white space
	// (Because individual components have spaces as well)
	replaceAll(rawPairS, " (", pairSep);

	// Remove extra bracket at end
	replaceAll(rawPairS, ")", "");
	
	// Split into player and character (2 parts)
	// e.g. 'davo1776' and 'Wario'
	vector<string> curPairParts = split(rawPairS, pairSep, 2);
	
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