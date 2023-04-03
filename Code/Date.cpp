// Date.cpp : 
// Defines Date class

// Header file
#include "Date.h"

// Namespace mods
using namespace std;


// Default Constructor
Date::Date()
{
	intYMD = DateM();
}


// Construct a date from a YMD
Date::Date(DateM newYMD)
{
	intYMD = newYMD;
}


// Construct a date from a string
// e.g. "2021-08-24 11.44 AM"
Date::Date(string rawDateS)
{
	// Split raw date into 3 parts
	// e.g. '2021-08-24',  '11.44', 'AM'
	stringV rawParts = split(rawDateS, " ", 3);

	// Get date part only (first part)
	string datePart = rawParts.front();
	stringstream ss(datePart);

	// Holder
	DateM newYMD;

	// Convert date string into date object
	chrono::from_stream(ss, "%F", newYMD);

	// If date is not valid
	if (!newYMD.ok())
	{
		// Notify
		print("WARNING: Invalid date detected!");
		print("Raw Date: " + rawDateS);

		// Try to fix
		auto sysTime = chrono::sys_time<chrono::days>{ newYMD };
		auto fixedYMD = chrono::year_month_day{ sysTime };

		// If valid and year is not negative
		if (fixedYMD.ok() && int(fixedYMD.year()) > 0)
		{
			// Has been successfully fixed, so:
			// Update field with fixed date
			newYMD = fixedYMD;

			// Notify
			print("Date should be: " + format("{:%Y-%m-%d}", newYMD));
			print("Please rename file accordingly", true);
		}
		else
		{
			// Else if it couldn't be fixed, notify
			print("ERROR: Couldn't fix date automatically");
			print("Fix attempt: " + format("{:%Y-%m-%d}", fixedYMD));
			print("Please fix manually", true);
		}
	}

	// Save holder into field
	intYMD = newYMD;
}


// Extract internal date
DateM Date::getYMD()
{
	return intYMD;
}


// Get date string in preferred format
// Format codes: 
// https://en.cppreference.com/w/cpp/chrono/year_month_day/formatter
string Date::toString()
{
	return format("{:%d/%b/%Y}", intYMD);
}