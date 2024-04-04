// MatchList.cpp
#include "MatchList.h"

// Namespace mods
using namespace std;
namespace fs = filesystem;


MatchList::MatchList()
{
	this->matches = vector<Match>();
}


MatchList::MatchList(string replayPath, bool onlineMatchesOnly)
{
	// If path is not valid
	if (!fs::exists(replayPath))
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
		[](Match m1, Match m2) {

			return m2.isMatchNewer(m1);
		});
}


void MatchList::printInfo()
{
	for (Match curM : matches)
	{
		print(curM.toString());
	}
}



int MatchList::getSize()
{
	return int(matches.size());
}


string MatchList::getSizeS()
{
	return to_string(getSize());
}


vector<Match> MatchList::getMatches()
{
	return matches;
}


Date MatchList::getFirstMatchDate()
{
	return matches.front().getDate();
}


Date MatchList::getLastMatchDate()
{
	return matches.back().getDate();
}


vector<Match> MatchList::getVersionMatches(string version)
{
	return getVariantMatches([&](Match lm)
		{
			return lm.getVersion() == version;
		});
}


vector<Match> MatchList::getYearMatches(string year)
{
	return getVariantMatches([&](Match lm)
		{
			return lm.getYear() == stoi(year);
		});
}


vector<Match> MatchList::getPlayerMatches(string playerName)
{
	return getVariantMatches([&](Match lm)
		{
			return vecContains(lm.getFighters().getPlayers(), playerName);
		});
}


vector<Match> MatchList::getCharMatches(string charName)
{
	return getVariantMatches([&](Match lm)
		{
			return vecContains(lm.getFighters().getChars(), charName);
		});
}


vector<Match> MatchList::getVariantMatches(VarMatchChecker hasVariant)
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