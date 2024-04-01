// Date.cpp
#include "Date.h"

// Namespace mods
using namespace std;
using namespace std::chrono;

// Initialize static fixed date list
vector<StringPair> Date::fixedDates;


Date::Date()
{
	// Get current system time
	auto now = system_clock::now();

	// Convert system time to nearest whole day and save
	intYMD = DateM(floor<days>(now));
}


Date::Date(DateM newYMD)
{
	intYMD = newYMD;
}


Date::Date(string dateS)
{
	// Convert date stream into a date object
	stringstream ss(dateS);
	DateM newYMD;
	chrono::from_stream(ss, "%F", newYMD);

	// Fix the date if needed
	DateM validYMD = fixDate(newYMD, dateS);
	
	// If date was changed (fixed), add to list of fixed dates
	if (newYMD != validYMD)
	{
		string validDateS = toOrigString(validYMD);
		fixedDates.push_back(make_pair(dateS, validDateS));
	}

	// Save fixed date
	this->intYMD = validYMD;
}


DateM Date::fixDate(DateM dateIn, string dateS)
{
	// If the date is valid, return it
	if (isValid(dateIn))
	{
		return dateIn;
	}

	// Else if the date is invalid, try to fix it
	DateM newDate = DateM{ sys_time<days>{ dateIn } };

	// If the date is now valid, return the fixed date
	if (isValid(newDate))
	{
		return newDate;
	}

	// Else if the new date is still invalid

	// # Make a version of the inputted date with one less day
	// Split date (e.g. 2021-08-24) into parts. e.g. '2021','08','24'
	StringV dateParts = split(dateS, "-", 3);
	year yearIn = year(stoi(dateParts.front()));
	month monthIn = month(stoi(dateParts[1]));
	day dayIn = day(stoi(dateParts.back()) - 1);
	DateM modifiedDateIn = DateM(yearIn, monthIn, dayIn);

	// Recursively run the modified date through the function again
	return fixDate(modifiedDateIn, toOrigString(modifiedDateIn));
}


bool Date::isValid(DateM date)
{
	return date.ok() && int(date.year()) > 0;
}


DateM Date::getYMD()
{
	return intYMD;
}


string Date::toString()
{
	return format("{:%d/%b/%Y}", intYMD);
}


string Date::toOrigString(DateM date)
{
	return format("{:%Y-%m-%d}", date);
}


string Date::getAbsTimePeriod(Date dateIn)
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

	// # 5. Remove leading duration parts that are zero
	if (yearS == "0")
	{
		yearS = "";
		if (monthS == "0")
		{
			monthS = "";
		}
	}

	// # 6. Add non-empty strings to result
	string durationS = "";

	if (yearS != "")
	{
		durationS += yearS + "y,";
	}

	if (monthS != "")
	{
		durationS += monthS + "m,";
	}

	durationS += dayS + "d";

	// Return result
	return durationS;
}


void Date::printFixedDates()
{
	// Heading
	print("\n# Invalid dates that were fixed (before and after)");

	// Get list of unique date errors
	std::map<string, int> dateFixMap;
	for (StringPair fixedDate : fixedDates)
	{
		// Format string pair as string
		string curFixS = format("{} -> {}", fixedDate.first, fixedDate.second);

		// Increment the count of the variant (or add it to the map)
		dateFixMap[curFixS]++;
	}

	// Print out map of unique "date fixes"
	for (auto const& uniqueFix : dateFixMap)
	{
		print(format("{} (x{})", uniqueFix.first, uniqueFix.second));
	}
}