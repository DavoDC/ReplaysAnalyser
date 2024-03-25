#pragma once

// ReplaysAnalyser.h
// Analyses replays by calculating statistics

// ### Headers
// Include common
#include "Common.h"

// Helper classes
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

	// ### Private methods
	std::string getReplayPath();
};

