// ReplaysAnalyser.cpp
#include "ReplaysAnalyser.h"

// Namespace mods
using namespace std;


// Constructor
ReplaysAnalyser::ReplaysAnalyser()
{
	this->customPath = "";
	this->ignoredPlayers = StringV{ AliasHandler::ANON };
	this->playerCutoff = 0.45;
	this->charCutoff = 1.0;
	this->onlineMatchesOnly = false;
}


// Setting functions
void ReplaysAnalyser::useSampleData()
{
	setCustomPath("../Sample_Data");
}

void ReplaysAnalyser::setCustomPath(string pathInput)
{
	this->customPath = pathInput;
}

void ReplaysAnalyser::setCustomLocalPath(string path)
{
	setCustomPath(format("C:/Users/David/{}", path));
}

void ReplaysAnalyser::setCustomLocalDwlFolder(string folderName)
{
	setCustomLocalPath(format("Downloads/{}", folderName));
}

void ReplaysAnalyser::setCustomLocalRepoFolder(string folderName)
{
	setCustomLocalPath(format("GitHubRepos/{}", folderName));
}

void ReplaysAnalyser::addIgnoredPlayer(string playerName)
{
	this->ignoredPlayers.push_back(playerName);
}

void ReplaysAnalyser::setPlayerCutoff(double newPlayerCutoff)
{
	this->playerCutoff = newPlayerCutoff;
}

void ReplaysAnalyser::setCharCutoff(double newCharCutoff)
{
	this->charCutoff = newCharCutoff;
}

void ReplaysAnalyser::setOfflinePlayerAliases(string p1Name, string p2Name)
{
	AliasHandler::setOfflinePlayerNames(p1Name, p2Name);
}

void ReplaysAnalyser::toggleOnlineMatchesOnly()
{
	onlineMatchesOnly = !onlineMatchesOnly;
}


// ### Main Method: Do analysis
void ReplaysAnalyser::analyse()
{
	// Welcome message
	print("####### WELCOME TO REPLAYS ANALYSER #######");

	// Parse replays and notify
	string replayPath = getReplayPath();
	MatchList ml = MatchList(replayPath, onlineMatchesOnly);
	print(format("\nParsing matches in '{}'...", replayPath));
	print(format("Parsed {} matches!", ml.getSizeS()));
	if (onlineMatchesOnly)
	{
		print("NOTE: Only online matches were included!");
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
		[](MatchList lml, string lvariant) -> vector<Match> {
			return lml.getVersionMatches(lvariant);
		});
	statP.printStatsList("Version", versionStats.getStatList());


	// 3) Year stats
	StatList yearStats = StatList(ml,
		[](Match m) -> StringV {
			return StringV{ m.getYearS() };
		},
		StringV(), 0,
		[](MatchList lml, string lvariant) -> vector<Match> {
			return lml.getYearMatches(lvariant);
		});
	statP.printStatsList("Year", yearStats.getStatList());


	// 4) Player stats
	StatList playerStats = StatList(ml,
		[](Match m) -> StringV {
			return m.getFighters().getPlayers();
		},
		ignoredPlayers, playerCutoff,
		[](MatchList lml, string lvariant) -> vector<Match> {
			return lml.getPlayerMatches(lvariant);
		});
	statP.printStatsList("Player", playerStats.getStatList());


	// 5) Character stats
	StatList charStats = StatList(ml,
		[](Match m) -> StringV {
			return m.getFighters().getChars();
		},
		StringV(), charCutoff,
		[](MatchList lml, string lvariant) -> vector<Match> {
			return lml.getCharMatches(lvariant);
		});
	statP.printStatsList("Character", charStats.getStatList());
}


// Helper: Get replay path
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