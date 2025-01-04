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


void StatPrinter::printPlayerSpecCharStats(const StringStatListPairV& playerSpecCharStats)
{
	// Print headings
	printHeading("Player-Specific Character");
	printPlayerSpecCharStatCol("#", "Player", "Char1 (%)", "Char2 (%)", "Char3 (%)");

	// Print each stat
	for (int i = 0; i < playerSpecCharStats.size(); i++)
	{
		// Extract stat pair
		StringStatListPair curStatPair = playerSpecCharStats.at(i);

		// Extract character stat list
		vector<Stat> charStatList = curStatPair.second.getStatList();
			
		// Print columns
		printPlayerSpecCharStatCol(
			to_string(i + 1), // Position
			curStatPair.first, // Player name
			getConcisePlayerSpecCharStat(charStatList, 0), // 1st Character name and percentage
			getConcisePlayerSpecCharStat(charStatList, 1), // 2nd Character name and percentage
			getConcisePlayerSpecCharStat(charStatList, 2)  // 3rd Character name and percentage
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


void StatPrinter::printPlayerSpecCharStatCol(const string& c1, const string& c2, const string& c3,
	const string& c4, const string& c5)
{
	cout
		<< left
		<< "\n"
		<< setw(4) << c1
		<< setw(14) << c2
		<< setw(24) << c3
		<< setw(24) << c4
		<< c5;
}


string StatPrinter::getConcisePlayerSpecCharStat(const vector<Stat>& charStatList, int pos)
{
	if (pos < 0 || pos >= charStatList.size())
	{
		return "N/A (N/A)";
	}

	Stat characterStat = charStatList.at(pos);
	return format("{} ({})", characterStat.getVariantValue(), characterStat.getPercentage());
}