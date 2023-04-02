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
stringV split(string fullS, string sep)
{
	// Holder vector
	stringV parts;

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


// split(): Helper function for splitting strings, with check!
// exp = The expected number of parts
stringV split(string fullS, string sep, int exp)
{
	// Holder vector
	stringV parts = split(fullS, sep);

	// Get parts length
	int pLen = int(parts.size());

	// If number of parts doesn't match expected
	if (pLen != exp)
	{
		// Notify
		print("WARNING: Split had unexpected results!");
		string pLenS = to_string(pLen);
		string expS = to_string(exp);
		print(format("Expected [{}] parts but got [{}]", expS, pLenS));
		print(format("Call: split({}, {}, {})", fullS, sep, exp), true);
	}

	// Return vector
	return parts;
}

// replaceAll(): Helper function for removing substrings
// source = The original string, will be modified
// from = The substring to replace
// to = The string to be substituted in
void replaceAll(string& source, const string& from, const string& to)
{
	string newString;
	newString.reserve(source.length());  // Avoids a few memory allocations
	string::size_type lastPos = 0;
	string::size_type findPos;
	while (string::npos != (findPos = source.find(from, lastPos)))
	{
		newString.append(source, lastPos, findPos - lastPos);
		newString += to;
		lastPos = findPos + from.length();
	}
	newString += source.substr(lastPos);
	source.swap(newString);
}


// contains(): Helper function (wrapper)
// Returns true if the 1st string contains the 2nd
bool contains(string s1, string s2)
{
	// Return true if s1 contains s2
	return strstr(s1.c_str(), s2.c_str());
}