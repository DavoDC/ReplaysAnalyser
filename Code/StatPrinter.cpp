// StatPrinter.cpp
#include "StatPrinter.h"

// Namespace mods
using namespace std;


StatPrinter::StatPrinter()
{
}


void StatPrinter::printDateStats(Date oldest, Date newest)
{
	// Print headings
	printHeading("Date");
	
	// Print column headings
	printDateColumns("Current Date", "Date Range", "Time Period");

	// Get info
	string curDate = Date().toString();
	string dateRange = formatDateRange(oldest.toString(), newest.toString());
	string timePeriod = oldest.getAbsTimePeriod(newest);

	// Print info
	printDateColumns(curDate, dateRange, timePeriod);
}


void StatPrinter::printStatsList(string statName, vector<Stat> statList)
{
	// Print heading 
	printHeading(statName);

	// Print column headings
	printStatColumns("%", statName, "Matches", "Date Range", "Time Period");

	// Print each stat
	for (Stat curStat : statList)
	{
		printStat(curStat);
	}
}


void StatPrinter::printHeading(string statName)
{
	print(format("\n### {} Statistics ###", statName));
}


string StatPrinter::formatDateRange(string date1, string date2)
{
	return format("{} - {}", date1, date2);
}


void StatPrinter::printDateColumns(string c1, string c2, string c3)
{
	cout
		<< left
		<< "\n"
		<< setw(15) << c1
		<< setw(30) << c2
		<< setw(10) << c3;
}


void StatPrinter::printStat(Stat stat)
{
	printStatColumns(
		stat.getPercentage(),
		stat.getVariantValue(), stat.getVariantCount(),
		formatDateRange(stat.getOldestDate(), stat.getNewestDate()),
		stat.getTimePeriod()
	);
}


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