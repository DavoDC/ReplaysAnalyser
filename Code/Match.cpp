// Match.cpp
#include "Match.h"

// Namespace mods
using namespace std;


Match::Match() : version(""), date(Date()), onlineMatch(false), fighters(FighterList())
{
}


Match::Match(const string& replayPath)
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


int Match::getYear() const
{
	return int(date.getYMD().year());
}


Date Match::getDate() const
{
	return date;
}


bool Match::isOnlineMatch() const
{
	return onlineMatch;
}


string Match::getYearS() const
{
	return to_string(getYear());
}


string Match::getDateS() const
{
	return date.toString();
}


const string& Match::getVersion() const
{
	return version;
}


const FighterList& Match::getFighters() const
{
	return fighters;
}


string Match::toString() const
{
	string result = date.toString();
	result += ", V:" + version;
	result += ", " + fighters.toString();
	return result;
}


const bool Match::isMatchNewer(const Match& mInput) const
{
	return this->getDate().getYMD() > mInput.getDate().getYMD();
}