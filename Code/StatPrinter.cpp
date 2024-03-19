// StatPrinter.cpp : 
// Defines StatPrinter class

// Header file
#include "StatPrinter.h"

// Namespace mods
using namespace std;


// Default Constructor
StatPrinter::StatPrinter()
{
}

// ### METHODS
// Print overall date statistics
void StatPrinter::printDateStats(Date oldest, Date newest)
{
	// Print headings
	printHeading("Date");
	
	// Print column headings
	printDateColumns("Current Date", "Date Range", "Duration");

	// Get info
	string curDate = Date().toString();
	string dateRange = formatDateRange(oldest.toString(), newest.toString());
	string duration = oldest.getAbsDuration(newest);

	// Print info
	printDateColumns(curDate, dateRange, duration);
}


// Print out a list of statistics objects
void StatPrinter::printStatsList(string statName, vector<Stat> statList)
{
	// Print heading 
	printHeading(statName);

	// Print column headings
	printStatColumns("%", statName, "Matches", "Date Range", "Duration");

	// Print each stat
	for (Stat curStat : statList)
	{
		printStat(curStat);
	}
}


// ### HELPERS
// Print heading for a section of statistics
void StatPrinter::printHeading(string statName)
{
	print(format("\n### {} Statistics ###", statName));
}

// Helper: Format two dates representing a range
string StatPrinter::formatDateRange(string date1, string date2)
{
	return format("{} - {}", date1, date2);
}

// Helper: Print out date columns
void StatPrinter::printDateColumns(string c1, string c2, string c3)
{
	cout
		<< left
		<< "\n"
		<< setw(15) << c1
		<< setw(30) << c2
		<< setw(10) << c3;
}

// Helper: Print out statistic
void StatPrinter::printStat(Stat stat)
{
	printStatColumns(
		stat.getPercentage(),
		stat.getVariantValue(), stat.getVariantCount(),
		formatDateRange(stat.getOldestDate(), stat.getNewestDate()),
		stat.getDuration()
	);
}

// Helper: Print out statistic columns
void StatPrinter::printStatColumns(string c1, string c2, string c3, 
	string c4, string c5)
{
	cout
		<< left
		<< "\n"
		<< setw(10) << c1
		<< setw(15) << c2
		<< setw(10) << c3
		<< setw(30) << c4
		<< c5;
}