// ReplayDate.cpp : 
// Defines ReplayDate class

// Header file
#include "ReplayDate.h"

// Namespace mods
using namespace std;


// Default Constructor
ReplayDate::ReplayDate()
{
	YMD = chrono::year_month_day();
}


// Construct a date from a string
ReplayDate::ReplayDate(string rawDateS)
{
	// Split raw date into date, time and AM/PM
	vector<string> rawParts = split(rawDateS, " ");

	// Get date part only
	string datePart = rawParts.front();

	// Convert into date object
    stringstream ss(datePart);
	chrono::year_month_day newYMD;
	chrono::from_stream(ss, "%F", newYMD);

    // Save into field
	YMD = newYMD;
}


// Extract internal date
chrono::year_month_day ReplayDate::getYMD()
{
	return YMD;
}


// Get date string in preferred format
string ReplayDate::toString()
{
	return format("{:%d %A, %m %B, %Y}", YMD);
}