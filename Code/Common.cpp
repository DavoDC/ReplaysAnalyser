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
// Returns the parts as a vector
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

// replaceAll(): Helper function for removing substrings
// source = The original string
// from = The substring to replace
// to = The string to be substituted in
void replaceAll(std::string& source, const std::string& from, const std::string& to)
{
	std::string newString;
	newString.reserve(source.length());  // Avoids a few memory allocations
	std::string::size_type lastPos = 0;
	std::string::size_type findPos;
	while (std::string::npos != (findPos = source.find(from, lastPos)))
	{
		newString.append(source, lastPos, findPos - lastPos);
		newString += to;
		lastPos = findPos + from.length();
	}
	newString += source.substr(lastPos);
	source.swap(newString);
}