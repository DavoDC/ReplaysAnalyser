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
	printColumns("#", "%", "Current Date", "Fixed", "First Date (Time Since)", "Last Date (Time Since)", "Time Period");

	// Current Date
	Date currentDate = Date();
	string curDateS = currentDate.toString();

	// Fixed
	string fixedDateCount = Date::getFixedDateCountS();

	// First and last dates (and time passed)
	string firstDate = getDateAndTimePassed(oldest, currentDate);
	string lastDate = getDateAndTimePassed(newest, currentDate);

	// Time Period
	string timePeriod = oldest.getAbsTimePeriod(newest);

	// Print info in columns
	printColumns("N/A", "N/A", curDateS, fixedDateCount, firstDate, lastDate, timePeriod);

}


void StatPrinter::printStatsList(const string& statName, const vector<Stat>& statList)
{
	// Print headings
	printHeading(statName);
	printColumns("#", "%", statName, "Matches", "First Date (Time Since)", "Last Date (Time Since)", "Time Period");

	// Print each stat
	Date currentDate = Date();
	for (int i = 0; i < statList.size(); i++)
	{
		Stat curStat = statList.at(i);
		printColumns(
			to_string(i + 1), // Position
			curStat.getPercentage(), // %
			curStat.getVariantValue(), // statName
			curStat.getVariantCount(), // Matches
			getDateAndTimePassed(curStat.getOldestDate(), currentDate), // First Date
			getDateAndTimePassed(curStat.getNewestDate(), currentDate), // Last Date
			curStat.getTimePeriod() // Time Period
		);
	}
}


void StatPrinter::printHeading(const string& statName)
{
	print(format("\n### {} Statistics ###", statName));
}


string StatPrinter::getDateAndTimePassed(const Date& date, const Date& currentDate)
{
	return format("{} ({})", date.toString(), date.getAbsTimePeriod(currentDate));
}


void StatPrinter::printColumns(const string& c1, const string& c2, const string& c3,
	const string& c4, const string& c5, const string& c6, const string& c7)
{
	cout
		<< left
		<< "\n"
		<< setw(4) << c1
		<< setw(8) << c2
		<< setw(16) << c3
		<< setw(9) << c4
		<< setw(26) << c5
		<< setw(26) << c6
		<< c7;
}