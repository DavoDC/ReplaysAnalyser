// ReplaysAnalyser.cpp
#include "ReplaysAnalyser.h"

// Namespace mods
using namespace std;


ReplaysAnalyser::ReplaysAnalyser()
{
	this->customPath = "";
	this->ignoredPlayers = StringV{ AliasHandler::ANON };
	this->playerCutoff = 0.45;
	this->charCutoff = 1.25;
	this->onlineMatchesOnly = false;
	this->printReviewMessages = false;
}


void ReplaysAnalyser::useSampleData()
{
	setCustomPath("../Sample_Data");
}


void ReplaysAnalyser::setCustomPath(const string& pathInput)
{
	this->customPath = pathInput;
}


void ReplaysAnalyser::setCustomLocalPath(const string& path)
{
	setCustomPath(format("C:/Users/David/{}", path));
}


void ReplaysAnalyser::setCustomLocalDwlFolder(const string& folderName)
{
	setCustomLocalPath(format("Downloads/{}", folderName));
}


void ReplaysAnalyser::setCustomLocalRepoFolder(const string& folderName)
{
	setCustomLocalPath(format("GitHubRepos/{}", folderName));
}


void ReplaysAnalyser::addIgnoredPlayer(const string& playerName)
{
	this->ignoredPlayers.push_back(playerName);
}


void ReplaysAnalyser::setPlayerCutoff(const double& newPlayerCutoff)
{
	this->playerCutoff = newPlayerCutoff;
}


void ReplaysAnalyser::setCharCutoff(const double& newCharCutoff)
{
	this->charCutoff = newCharCutoff;
}


void ReplaysAnalyser::setOfflinePlayerAliases(const string& p1Name, const string& p2Name)
{
	AliasHandler::setOfflinePlayerNames(p1Name, p2Name);
}


void ReplaysAnalyser::toggleOnlineMatchesOnly()
{
	onlineMatchesOnly = !onlineMatchesOnly;
}


void ReplaysAnalyser::togglePrintingReviewMessages()
{
	printReviewMessages = !printReviewMessages;
}


void ReplaysAnalyser::printFixedDates()
{
	Date::printFixedDates();
}


void ReplaysAnalyser::analyse()
{
	// Welcome message
	print("####### WELCOME TO REPLAYS ANALYSER #######");

	// Parse replays and notify when done
	string replayPath = getReplayPath();
	print(format("\nParsing matches in '{}'...", replayPath));
	MatchList ml = MatchList(replayPath, onlineMatchesOnly);
	print(format("Parsed {} matches!", ml.getSizeS()));

	// If "online only" enabled, notify
	if (onlineMatchesOnly)
	{
		print("NOTE: Only online matches were included!");
	}

	// Notify if there were any fixed/invalid dates
	string datesFixed = Date::getFixedDateCountS();
	if (stoi(datesFixed) == 0)
	{
		print("NOTE: All dates were valid!");
	}
	else
	{
		warn("Invalid date(s) found!", datesFixed);
	}

	// Create statistics printer
	StatPrinter statP = StatPrinter();

	// ### Print statistics
	// 1) Date stats
	statP.printDateStats(ml.getFirstMatchDate(), ml.getLastMatchDate());


	// 2) Version stats
	StatList versionStats = StatList(ml,
		[](Match lm) -> StringV {
			return StringV{ lm.getVersion() };
		},
		StringV(), 0,
		[](const MatchList& lml, const string& lvariant) -> vector<Match> {
			return lml.getVersionMatches(lvariant);
		});
	statP.printStatsList("Version", versionStats.getStatList());


	// 3) Year stats
	StatList yearStats = StatList(ml,
		[](Match m) -> StringV {
			return StringV{ m.getYearS() };
		},
		StringV(), 0,
		[](const MatchList& lml, const string& lvariant) -> vector<Match> {
			return lml.getYearMatches(lvariant);
		});
	statP.printStatsList("Year", yearStats.getStatList());


	// 4) Player stats
	StatList playerStats = StatList(ml,
		[](Match m) -> StringV {
			return m.getFighters().getPlayers();
		},
		ignoredPlayers, playerCutoff,
		[](const MatchList& lml, const string& lvariant) -> vector<Match> {
			return lml.getPlayerMatches(lvariant);
		});
	statP.printStatsList("Player", playerStats.getStatList());


	// 5) Character stats
	StatList charStats = StatList(ml,
		[](Match m) -> StringV {
			return m.getFighters().getChars();
		},
		StringV(), charCutoff,
		[](const MatchList& lml, const string& lvariant) -> vector<Match> {
			return lml.getCharMatches(lvariant);
		});
	statP.printStatsList("Character", charStats.getStatList());


	// 6) Player-specific character stats
	vector<PlayerSpecStatList> playerSpecCharStats = getPlayerSpecificCharStats(ml);
	statP.printPlayerSpecCharStats(playerSpecCharStats);

	// 7) Review messages
	if (printReviewMessages)
	{
		statP.printPlayerReviewMessages(playerStats.getStatList(), playerSpecCharStats);
	}
}


string ReplaysAnalyser::getReplayPath()
{
	// # If custom path set, use it
	if (customPath != "")
	{
		return customPath;
	}

	// # Otherwise, try to find default replay path for this user
	string replayPath = string("C:/Users/");

	// Get username from environment variable
	string username = "David";
	char* buf = nullptr;
	size_t sz = 0;
	if (_dupenv_s(&buf, &sz, "USERNAME") == 0 && buf != nullptr) {
		username = string(buf);
		free(buf);
	}
	else {
		print("\nError reading %USERNAME% !!!");
	}

	// Add username and folder
	replayPath += username + string("/SSF2Replays");

	// Return replay path
	return replayPath;
}


vector<PlayerSpecStatList> ReplaysAnalyser::getPlayerSpecificCharStats(const MatchList& fullMatchList)
{
	// Get ALL player stats with no ignored players, except ANON
	StatList allPlayerStats = StatList(fullMatchList,
		[](Match m) -> StringV {
			return m.getFighters().getPlayers();
		},
		StringV{ AliasHandler::ANON }, playerCutoff,
		[](const MatchList& lml, const string& lvariant) -> vector<Match> {
			return lml.getPlayerMatches(lvariant);
		});

	// To hold the list of each player's character stats
	vector<PlayerSpecStatList> playerSpecCharStats;

	// For every player stat
	double playerSpecificCharStatCharCutoff = 0.0;
	for (Stat playerStat : allPlayerStats.getStatList())
	{
		// Get this player's name and matches
		string playerName = playerStat.getVariantValue();
		MatchList playerMatches = playerStat.getVariantMatchList();

		// Calculate this player's character stats from their matches and add to list
		playerSpecCharStats.emplace_back(playerName, playerMatches,
			[&playerName](Match m) -> StringV {
				return StringV{ m.getFighters().getChar(playerName) };
			},
			StringV(), playerSpecificCharStatCharCutoff,
			[](const MatchList& lml, const std::string& lvariant) -> std::vector<Match> {
				return lml.getCharMatches(lvariant);
			});
	}

	// Return result
	return playerSpecCharStats;
}