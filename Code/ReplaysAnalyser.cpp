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
	this->cutoff = 0.6;
	this->columnPrint = true;
	this->matchNum = 0;
}


// ### Setters
// Toggle sample data
void ReplaysAnalyser::toggleSampleData()
{
	useSampleData = !useSampleData;
}

// Set cut off
// newCutoff = Percentage value (e.g. 5.0 = 5%)
void ReplaysAnalyser::setCutoff(double newCutoff)
{
	cutoff = newCutoff;
}


// ### Main Method: Do analysis
void ReplaysAnalyser::analyse()
{
	// Welcome message
	print("####### WELCOME TO REPLAYS ANALYSER #######");

	// Parse replays and notify
	ml = MatchList(getReplayPath());
	matchNum = ml.getSize();
	print("\nParsed " + ml.getSizeS() + " matches!");

	// Create statistics printer
	StatPrinter statP = StatPrinter();

	// ### Print statistics
	// 1) Date stats
	statP.printHeading("Date");
	statP.printCurDate(Date().toString());
	statP.printDateRange(ml.getMatches().front().getDate().toString(), 
		ml.getMatches().back().getDate().toString());

	// 2) Version stats
	statP.printHeading("Version");
	StatList versionStats = StatList(ml,
		[](Match lm) -> StringV {
			return StringV{ lm.getVersion() };
		},
		StringV(), cutoff,
		[](MatchList lml, string lvariant) -> vector<Match> {
			return lml.getVersionMatches(lvariant);
		});
	statP.printStatsList(versionStats.getStatList());


	//// 3) Year stats
	//printFreqStats("Year",
	//	[](Match m) -> StringV {
	//		return StringV{ to_string(m.getYear()) };
	//	});

	//// 4) Player stats
	//printFreqStats("Player",
	//	[](Match m) -> StringV {
	//		return m.getFighters().getPlayers();
	//	});

	//// 5) Character stats
	//printFreqStats("Character",
	//	[](Match m) -> StringV {
	//		return m.getFighters().getChars();
	//	});
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