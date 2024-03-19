// Date.cpp : 
// Defines Date class

// Header file
#include "Date.h"

// Namespace mods
using namespace std;
using namespace std::chrono;


// Default Constructor
Date::Date()
{
	// Get current system time
	auto now = system_clock::now();

	// Convert system time to nearest whole day and save
	intYMD = DateM(floor<days>(now));
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
	// e.g. '2021-08-24', '11.44', 'AM'
	StringV rawParts = split(rawDateS, " ", 3);

	// Extract date part as a string steam
	stringstream ss(rawParts.front());

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
		auto sysTime = sys_time<days>{ newYMD };
		auto fixedYMD = DateM{ sysTime };

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
			print("ERROR: Couldn't fix date automatically!");
			print("Fix attempt: " + format("{:%Y-%m-%d}", fixedYMD));
			print("Please fix manually!", true);
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


// Get absolute duration compared to another date
string Date::getAbsDuration(Date dateIn)
{
	// # 0. Calculate absolute difference in days
	days dayDiff = abs(sys_days(this->intYMD) - sys_days(dateIn.intYMD));

    // # 1. Get years and subtract years
	// Convert difference to years
	years yearVal = duration_cast<years>(dayDiff);

	// Convert years to days and subtract from difference
	dayDiff = dayDiff - duration_cast<days>(yearVal);

	// # 2. Get months and subtract months
	// Convert difference to months
	months monthVal = duration_cast<months>(dayDiff);
	
	// Convert months to days and subtract from difference
	dayDiff = dayDiff - duration_cast<days>(monthVal);

	// # 3. Get days
	// Convert difference to days
	days dayVal = duration_cast<days>(dayDiff);

	// # 4. Convert to strings
	string yearS = to_string(yearVal.count());
	string monthS = to_string(monthVal.count());
	string dayS = to_string(dayVal.count());

	// Return strings formatted together
	return format("{}y, {}m, {}d", yearS, monthS, dayS);
}