// ReplaysAnalyser.cpp : 
// Defines ReplaysAnalyser class

// Include header file
#include "ReplaysAnalyser.h"

// Namespace mods
using namespace std;


// Constructor
ReplaysAnalyser::ReplaysAnalyser()
{
	// Set variables to default values
	this->useSampleData = false;
}


// Toggle sample data
void ReplaysAnalyser::toggleSampleData()
{
	useSampleData = !useSampleData;
}


// ### Main Method: Do analysis
void ReplaysAnalyser::analyse()
{
	// Welcome message
	print("####### WELCOME TO REPLAYS ANALYSER #######");

	// Parse replays and notify
	string replayPath = getReplayPath();
	print(format("\nParsing matches in '{}'...", replayPath));
	MatchList ml = MatchList(replayPath);
	print(format("Parsed {} matches!", ml.getSizeS()));

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
		StringV{ "davo", AliasHandler::ANON }, 0.4,
		[](MatchList lml, string lvariant) -> vector<Match> {
			return lml.getPlayerMatches(lvariant);
		});
	statP.printStatsList("Player", playerStats.getStatList());


	// 5) Character stats
	StatList charStats = StatList(ml,
		[](Match m) -> StringV {
			return m.getFighters().getChars();
		},
		StringV(), 1.0,
		[](MatchList lml, string lvariant) -> vector<Match> {
			return lml.getCharMatches(lvariant);
		});
	statP.printStatsList("Character", charStats.getStatList());
}


// Helper: Get replay path
string ReplaysAnalyser::getReplayPath()
{
	// If sample data wanted, use it instead
	if (useSampleData)
	{
		return string("../Sample_Data");
	}

	// Holder
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