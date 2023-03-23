// ReplayDate.cpp : 
// Defines ReplayDate class

// Header file
#include "ReplayDate.h"

// Namespace mods
using namespace std;


// Default Constructor
ReplayDate::ReplayDate()
{
	YMD = DateM();
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
	DateM newYMD;
	chrono::from_stream(ss, "%F", newYMD);

	// If date is not valid
	if (!newYMD.ok())
	{
		// TEMP
		print("WARNING: Invalid date generated");
		print("Bad date was: " + rawDateS);

		// Try to fix
		auto sysTime = chrono::sys_time<chrono::days>{ newYMD };
		auto fixedYMD = chrono::year_month_day{ sysTime };

		// If valid and year is not negative
		if (fixedYMD.ok() && int(fixedYMD.year()) > 0)
		{
			// It has been fixed, so save it
			newYMD = fixedYMD;

			// TEMP
			print("Date should be: " + format("{:%Y-%m-%d}", newYMD), true);
		}
		else
		{
			// Else if it couldn't be fixed, notify
			print("WARNING: Unfixable invalid date generated!");
			print("RDS was: " + rawDateS);
			print("Fix attempt: " + format("{:%d/%b/%Y}", fixedYMD));
		}
	
		
	}

	

	// Save into field
	YMD = newYMD;
}


// Extract internal date
DateM ReplayDate::getYMD()
{
	return YMD;
}


// Get date string in preferred format
// Format codes: 
// https://en.cppreference.com/w/cpp/chrono/year_month_day/formatter
string ReplayDate::toString()
{
	return format("{:%d/%b/%Y}", YMD);
}