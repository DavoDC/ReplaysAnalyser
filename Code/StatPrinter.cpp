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
// Print heading for a section of statistics
void StatPrinter::printHeading(string statName)
{
	print(format("\n### {} Statistics ###", statName));
}


// Print the current date
void StatPrinter::printCurDate(string curDateS)
{
	print(format("{} {}", "Current Date:", curDateS));
}

// Print the date range
void StatPrinter::printDateRange(string oldest, string newest)
{
	print(format("{} {}", "Date Range:", formatDateRange(oldest, newest)));
}


// Print out a list of statistics objects
void StatPrinter::printStatsList(vector<Stat> statList)
{
	// Print column headings
	printColumns("%", "TEMPORARY", "Matches", "Date Range");

	// Print each stat
	for (Stat curStat : statList)
	{
		printStat(curStat);
	}
}


// ### HELPERS
// Helper: Format two dates representing a range
string StatPrinter::formatDateRange(string date1, string date2)
{
	return format("{} - {}", date1, date2);
}

// Helper: Print out columns
void StatPrinter::printColumns(string c1, string c2, string c3, string c4)
{
	cout
		<< left
		<< "\n"
		<< setw(10) << c1
		<< setw(15) << c2
		<< setw(10) << c3
		<< c4;
}

// Helper: Print out statistic
void StatPrinter::printStat(Stat stat)
{
	printColumns(
		stat.getPercentage(),
		stat.getVariantValue(), stat.getVariantCount(),
		formatDateRange(stat.getOldestDate(), stat.getNewestDate())
	);
}