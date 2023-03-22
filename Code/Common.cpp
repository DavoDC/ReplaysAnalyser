// Common.cpp : 
// Helper functions commonly used

// Header file
#include "Common.h"

// ### Libraries

// For string splitting
#include <iomanip>
#include <ranges>
#include <string_view>

// Namespace mods
using namespace std;

// print(): Helper function for printing
// - s = String to print
// - useEndl = Give True if you want endl (False by default)
void print(string s, bool useEndl)
{
	cout << "\n" << s;
	if (useEndl) {
		cout << endl;
	}
}

// split(): Helper function for splitting strings
// fullS = The full string
// sep = The string that separates the parts
vector<string> split(string fullS, string sep)
{
	// Holder vector
	vector<string> parts;

	// For every part
	for (const auto curPart : views::split(fullS, sep)) {

		// Convert to string
		string curPartS = string(curPart.begin(), curPart.end());

		// Add to vector
		parts.push_back(curPartS);
	}

	// Return vector
	return parts;
}
