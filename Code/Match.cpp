// Match.cpp
#include "Match.h"

// Namespace mods
using namespace std;


// Default Constructor
Match::Match()
{
	version = "";
	date = Date();
	onlineMatch = false;
	fighters = FighterList();
}


// Construct a match from a raw replay path
// e.g. ../Sample_Data/1.3.1.1/2021-08-24 11.44 AM - 2021-08-24 11.44 AM......." 
Match::Match(string replayPath)
{
	// Split replay name into parts
	// e.g "..", "Sample_Data", "1.3.1.1"
	// "2021-08-24 11.44 AM - VersusOnline - davo1776 (Wario)......."
	StringV pathParts = split(replayPath, "/");

	// Extract and save version (2nd last part). e.g. 1.3.1.1, and check
	version = pathParts[pathParts.size() - 2];
	if (version.length() != 7)
	{
		warn("Unusual version string!", version);
	}

	// Extract replay name (last part)
	// e.g. 2021-08-24 11.44 AM - VersusOnline - davo1776 (Wario).......
	string filename = pathParts.back();

	// Split replay name into 3 parts
	// e.g "2021-08-24 11.44 AM", "VersusOnline"
	// "davo1776 (Wario) vs HexxaWyn (Naruto) ...."
	StringV replayParts = split(filename, " - ", 3);

	// # Extract date from first string. e.g. "2021-08-24 11.44 AM"
	// Split into 3 parts. e.g. '2021-08-24', '11.44', 'AM'
	StringV dateParts = split(replayParts.front(), " ", 3);
	// Make date from first part only. e.g. '2021-08-24'
	date = Date(dateParts.front());

	// Extract replay type from second string
	string replayType = replayParts[1];
	onlineMatch = contains(replayType, "Online");

	// Extract fighters from last string
	// e.g. "davo1776 (Wario) vs HexxaWyn (Naruto) ...."
	fighters = FighterList(replayParts.back(), replayType);
}


// Getters
int Match::getYear()
{
	return int(date.getYMD().year());
}

Date Match::getDate()
{
	return date;
}

bool Match::isOnlineMatch()
{
	return onlineMatch;
}

string Match::getYearS()
{
	return to_string(getYear());
}

string Match::getDateS()
{
	return date.toString();
}

string Match::getVersion()
{
	return version;
}

FighterList Match::getFighters()
{
	return fighters;
}



// Get a string representation of the match (one line)
string Match::toString()
{
	string result = date.toString();
	result += ", V:" + version;
	result += ", " + fighters.toString();
	return result;
}


/**
 * @return True if this match is newer than the one inputted
*/
bool Match::isMatchNewer(Match mInput)
{
	return this->getDate().getYMD() > mInput.getDate().getYMD();
}
