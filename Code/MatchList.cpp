// MatchList.cpp
#include "MatchList.h"

// Namespace mods
using namespace std;


MatchList::MatchList()
{
	this->matches = vector<Match>();
}

MatchList::MatchList(const vector<Match>& matchListIn)
{
	// Notify if input is empty
	if (matchListIn.empty())
	{
		print("Empty vector provided to MatchList constructor!");
	}

	this->matches = matchListIn;
}

MatchList::MatchList(const string& replayPath, const bool& onlineMatchesOnly)
{
	// If path is not valid
	if (!filesystem::exists(replayPath))
	{
		// Notify and exit
		print("\nMatchList(): Invalid Replay Path");
		print("\nPath was: " + replayPath + "\n");
		exit(EXIT_FAILURE);
	}

	// Check
	bool foundOneReplay = false;

	// For every path in the directory
	for (const auto& curPath : FSIterator(replayPath)) {

		// Convert current path to string
		string curPathS = curPath.path().generic_string();

		// If it is a replay path/file
		if (contains(curPathS, ".ssfrec")) {

			// Update check
			foundOneReplay = true;

			// Convert to Match 
			Match curMatch = Match(curPathS);

			// Add if passes online match filter, if enabled
			if (!onlineMatchesOnly || curMatch.isOnlineMatch())
			{
				matches.push_back(curMatch);
			}
		}
	}

	// If didn't find at least one replay
	if (!foundOneReplay)
	{
		// Notify and exit
		print("\nMatchList(): Empty Replay Folder");
		print("\nNo replays found!");
		print("\nPath was: " + replayPath + "\n");
		exit(EXIT_FAILURE);
	}

	// Sort matches by date
	sort(matches.begin(), matches.end(),
		[](const Match& m1, const Match& m2) {

			return m2.isMatchNewer(m1);
		});
}


const void MatchList::printInfo() const
{
	for (Match curM : matches)
	{
		print(curM.toString());
	}
}



const int MatchList::getSize() const
{
	return int(matches.size());
}


const string MatchList::getSizeS() const
{
	return to_string(getSize());
}


const vector<Match>& MatchList::getMatches() const
{
	return matches;
}


const Date MatchList::getFirstMatchDate() const
{
	return matches.front().getDate();
}


const Date MatchList::getLastMatchDate() const
{
	return matches.back().getDate();
}


const vector<Match> MatchList::getVersionMatches(const string& version) const
{
	return getVariantMatches([&](Match lm)
		{
			return lm.getVersion() == version;
		});
}


const vector<Match> MatchList::getYearMatches(const string& year) const
{
	return getVariantMatches([&](Match lm)
		{
			return lm.getYear() == stoi(year);
		});
}


const vector<Match> MatchList::getPlayerMatches(const string& playerName) const
{
	return getVariantMatches([&](Match lm)
		{
			return vecContains(lm.getFighters().getPlayers(), playerName);
		});
}


const vector<Match> MatchList::getCharMatches(const string& charName) const
{
	return getVariantMatches([&](Match lm)
		{
			return vecContains(lm.getFighters().getChars(), charName);
		});
}


const vector<Match> MatchList::getVariantMatches(const VarMatchChecker& hasVariant) const
{
	// Holder for the variant's matches
	vector<Match> variantMatches;

	// Copy in match if it has the variant
	std::copy_if(matches.begin(), matches.end(), std::back_inserter(variantMatches),
		[&](Match m)
		{
			return hasVariant(m);
		}
	);

	// Return result
	return variantMatches;
}