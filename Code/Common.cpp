// Common.cpp
#include "Common.h"
#include <ranges>
#include <string_view>
#include <algorithm>

// Namespace mods
using namespace std;


void print(const string& s, bool useEndl)
{
	cout << "\n" << s;
	if (useEndl) {
		cout << endl;
	}
}


void warn(const string& desc, const string& details)
{
	print(format("WARNING: {} ({})", desc, details));
}


StringV split(const string& fullS, const string& sep)
{
	StringV parts;
	auto subranges = std::views::split(fullS, sep);
	std::transform(subranges.begin(), subranges.end(),
		std::back_inserter(parts),
		[](const auto& curPart) {
			return string(curPart.begin(), curPart.end());
		});
	return parts;
}


StringV split(const string& fullS, const string& sep, const int& exp)
{
	// Split and get length
	StringV parts = split(fullS, sep);
	int pLen = int(parts.size());

	// If number of parts doesn't match expected
	if (pLen != exp)
	{
		// Notify
		string pLenS = to_string(pLen);
		string expS = to_string(exp);
		string comp = format("expected {} parts but got {}", expS, pLenS);
		warn("Unusual split!", comp);
		print(format("Call: split({}, {}, {})", fullS, sep, exp), true);
	}

	// Return vector
	return parts;
}


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


bool contains(const string& s1, const string& s2)
{
	return strstr(s1.c_str(), s2.c_str());
}


bool vecContains(const StringV& list, const string& value)
{
	if (list.empty())
	{
		return false;
	}
	return find(list.begin(), list.end(), value) != list.end();
}


bool equalsIgnoreCase(const string& str1, const string& str2) {
	return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(), 
		[](char a, char b) 
		{
			return std::tolower(a) == std::tolower(b);
		});
}