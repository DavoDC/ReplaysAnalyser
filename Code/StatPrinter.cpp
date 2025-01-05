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


void StatPrinter::printPlayerSpecCharStats(const vector<PlayerSpecStatList>& playerSpecCharStats)
{
	// Print headings
	printHeading("Player-Specific Character");
	printPlayerSpecCharStatCol("#", "Player", "Char1 (%)", "Char2 (%)", "Char3 (%)");

	// Print each stat
	for (int i = 0; i < playerSpecCharStats.size(); i++)
	{
		// Extract stat list for this player
		PlayerSpecStatList curPlayerStatList = playerSpecCharStats.at(i);

		// NOTE: To show complete character stats for each player:
		//printStatsList(curPlayerStatList.getPlayerName() + "'s", curPlayerStatList.getStatList());
			
		// Print columns
		printPlayerSpecCharStatCol(
			to_string(i + 1), // Position
			curPlayerStatList.getPlayerName(), // Player
			curPlayerStatList.getConciseStatS(0), // 1st Character name and percentage
			curPlayerStatList.getConciseStatS(1), // 2nd Character name and percentage
			curPlayerStatList.getConciseStatS(2)  // 3rd Character name and percentage
		);
	}
}


void StatPrinter::printPlayerReviewMessages(const vector<Stat>& playerStats, 
	const vector<PlayerSpecStatList>& playerSpecCharStats)
{
	// Print heading
	print("\n");
	printHeading("Player Review Messages, incl. ");

	// Get current date info
	Date curDate = Date();
	string curDateS = curDate.toString();

	// For every top player
	for (int i = 0; i < playerStats.size(); i++)
	{
		// Extract current player stat
		Stat curPlayerStat = playerStats.at(i);

		// Print line 1 - heading
		string chartEmoji = ":bar_chart:";
		string line1 = format("{} **SSF2 Replay Statistics Review** ({}) {}", chartEmoji, curDateS, chartEmoji);
		print("\n" + line1);
		
		// Print line 2 - hello
		string playerStatsName = curPlayerStat.getVariantValue();
		string line2 = format("Hey {}!", playerStatsName);
		print("\n" + line2);

		// Print line 3 - basic player stats
		int pos = i + 1;
		string rank = (i == 0) ? "my" : ("my " + to_string(pos) + ordinal(pos));
		string percentage = curPlayerStat.getPercentage();
		string amount = curPlayerStat.getVariantCount();
		string line3 = "Congratulations! :tada: ";
		line3 += format("You're {} most played-with player, ", rank);
		line3 += format("contributing to **{}** (**{}**) of my total replays!", percentage, amount);
		print("\n" + line3);

		// Print line 4,5,6 - date stat dot-points
		print(format("- First Match: {}", getDateAndTimePassed(curPlayerStat.getOldestDate(), curDate, true)));
		print(format("- Last Match: {}", getDateAndTimePassed(curPlayerStat.getNewestDate(), curDate, true)));
		print(format("- Time Played Together: {}", curPlayerStat.getTimePeriod()));

		// Print line 7,8,9,10 - character stat heading and dot-points
		PlayerSpecStatList curPlayerCharStat = playerSpecCharStats.at(i + 1); // Skip first player (myself)
		if (!curPlayerCharStat.isPlayer(playerStatsName))
		{
			string details = curPlayerCharStat.getPlayerName() + "!=" + playerStatsName;
			warn("Mismatch in player names provided to function", details);
			exit(0);
		}
		print("\nYour Top 3 Most Played Characters:");
		print(format("- {}", curPlayerCharStat.getConciseStatS(0)));
		print(format("- {}", curPlayerCharStat.getConciseStatS(1)));
		print(format("- {}", curPlayerCharStat.getConciseStatS(2)));

		// Print line 11 - full report link
		string link = "https://github.com/DavoDC/ReplaysAnalyser/blob/";
		link += "4eb8e0e6d5a530fd7077237228f348fce9a029d1/Reports/2025/2025-01-04%20-%20RA_REPORT.txt";
		string line11 = "If you want to dive deeper into the stats, "; 
		line11 += format("check out the full report here: <{}>", link);
		print("\n" + line11);

		// Print line 12 - ending
		string line12 = "Thanks for the games, Davo :slight_smile:";
		print("\n" + line12);

		// Space
		print("\n");
	}

	// Space
	print("\n");
}


void StatPrinter::printHeading(const string& statName)
{
	print(format("\n### {} Statistics ###", statName));
}


string StatPrinter::getDateAndTimePassed(const Date& date, const Date& currentDate, bool addAgo)
{
	string curDateS = date.toString();
	string timePeriodS = date.getAbsTimePeriod(currentDate);
	return format("{} ({})", curDateS, addAgo ? timePeriodS + " ago": timePeriodS);
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

string StatPrinter::ordinal(int n)
{
	if (n % 100 >= 11 && n % 100 <= 13) 
	{
		return "th";
	}

	switch (n % 10) 
	{
		case 1: return "st";
		case 2: return "nd";
		case 3: return "rd";
		default: return "th";
	}
}