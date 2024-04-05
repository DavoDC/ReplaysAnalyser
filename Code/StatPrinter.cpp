// StatPrinter.cpp
#include "StatPrinter.h"

// Namespace mods
using namespace std;


StatPrinter::StatPrinter()
{
}


void StatPrinter::printDateStats(const Date& oldest, const Date& newest)
{
	// Print headings
	printHeading("Date");
	printColumns("%", "Current Date", "Fixed", "Date Range", "Time Period", "Time Since Last");

	// Get info
	Date currentDate = Date();
	string curDateS = currentDate.toString();
	string fixedDateCount = Date::getFixedDateCountS();
	string dateRange = formatDateRange(oldest.toString(), newest.toString());
	string timePeriod = oldest.getAbsTimePeriod(newest);
	string timePassed = currentDate.getAbsTimePeriod(newest);

	// Print info in columns
	printColumns("N/A", curDateS, fixedDateCount, dateRange, timePeriod, timePassed);
	
}


void StatPrinter::printStatsList(const string& statName, const vector<Stat>& statList)
{
	// Print headings
	printHeading(statName);
	printColumns("%", statName, "Matches", "Date Range", "Time Period", "Time Since Last");

	// Print each stat
	for (Stat curStat : statList)
	{
		printStat(curStat);
	}
}


void StatPrinter::printHeading(const string& statName)
{
	print(format("\n### {} Statistics ###", statName));
}


void StatPrinter::printColumns(const string& c1, const string& c2,
	const string& c3, const string& c4, const string& c5, const string& c6)
{
	cout
		<< left
		<< "\n"
		<< setw(10) << c1
		<< setw(15) << c2
		<< setw(10) << c3
		<< setw(30) << c4
		<< setw(15) << c5
		<< c6;
}


string StatPrinter::formatDateRange(const string& date1, const string& date2)
{
	return format("{} - {}", date1, date2);
}


void StatPrinter::printStat(const Stat& stat)
{
	Date newestDate = stat.getNewestDate();

	printColumns(
		stat.getPercentage(),
		stat.getVariantValue(), stat.getVariantCount(),
		formatDateRange(stat.getOldestDate().toString(), newestDate.toString()),
		stat.getTimePeriod(), Date().getAbsTimePeriod(newestDate)
	);
}