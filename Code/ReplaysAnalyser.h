#pragma once

// ReplaysAnalyser.h
// Analyses replays by calculating statistics

#include "Common.h"
#include "MatchList.h"
#include "StatPrinter.h"
#include "StatList.h"

// Declare ReplaysAnalyser class
class ReplaysAnalyser {

public:

	// Constructor
	ReplaysAnalyser();

	// Setting functions
	void useSampleData();
	void setCustomPath(std::string path);
	void setCustomLocalPath(std::string path);
	void setCustomLocalDwlFolder(std::string folderName);
	void setCustomLocalRepoFolder(std::string folderName);
	void setCharCutoff(double newCharCutoff);
	void setPlayerCutoff(double newPlayerCutoff);
	void addIgnoredPlayer(std::string playerName);
	void setOfflinePlayerAliases(std::string p1name, std::string p2name);
	void toggleOnlineMatchesOnly();

	/**
	 * @brief See Date::printFixedDates()
	*/
	void printFixedDates();
	
	// Main function
	void analyse();

private:
	// ### Private fields
	
	// Custom replay path
	std::string customPath;

	// Ignored player list
	StringV ignoredPlayers;

	// Cutoffs
	double playerCutoff; 
	double charCutoff;

	// Online matches only
	bool onlineMatchesOnly;

	// ### Private methods
	std::string getReplayPath();
};

