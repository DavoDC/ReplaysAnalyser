#pragma once

// ReplaysAnalyser.h

#include "Common.h"
#include "MatchList.h"
#include "StatPrinter.h"
#include "StatList.h"

/**
 * @brief Analyses replays by calculating statistics
 */
class ReplaysAnalyser {

public:

	/**
	 * @brief Construct a default analyser
	*/
	ReplaysAnalyser();

	/**
	 * @brief Sets the replay path to the sample data folder
	*/
	void useSampleData();

	/**
	 * @brief Set a custom replay path to be analysed
	 * @param path - to a folder containing version folders and replays
	*/
	void setCustomPath(const std::string& path);

	/**
	 * @brief Set a custom replay path to be analysed within user folder
	 * @param path - folder within 'C:/Users/David/'
	*/
	void setCustomLocalPath(const std::string& path);

	/**
	 * @brief Set a custom replay path to be analysed within downloads folder
	 * @param path - folder within 'C:/Users/David/Downloads'
	*/
	void setCustomLocalDwlFolder(const std::string& folderName);

	/**
	 * @brief Set a custom replay path to be analysed within repo folder
	 * @param path - folder within 'C:/Users/David/GitHubRepos'
	*/
	void setCustomLocalRepoFolder(const std::string& folderName);

	/**
	 * @brief Set the percentage cutoff for character stats
	*/
	void setCharCutoff(const double& newCharCutoff);

	/**
	 * @brief Set the percentage cutoff for player stats
	*/
	void setPlayerCutoff(const double& newPlayerCutoff);

	/**
	 * @brief Add the given standard player name to list of players to ignore
	*/
	void addIgnoredPlayer(const std::string& playerName);

	/**
	 * @brief Link the offline players to standard names
	 * @param p1name The standard name of the player usually playing P1 locally
	 * @param p2name The standard name of the player usually playing P2 locally
	*/
	void setOfflinePlayerAliases(const std::string& p1name, const std::string& p2name);

	/**
	 * @brief Toggle only showing online matches
	*/
	void toggleOnlineMatchesOnly();

	/**
	 * @brief Toggle printing review messages
	*/
	void togglePrintingReviewMessages();

	/**
	 * @brief See Date::printFixedDates()
	*/
	void printFixedDates();
	
	/**
	 * @brief Print out the statistical analysis results
	*/
	void analyse();

private:

	/**
	 * @brief A custom path to the folder containing the desired replays
	 * If not set, it is ignored.
	*/
	std::string customPath;

	/**
	 * @brief A list of standard player names to ignore (remove from stats)
	*/
	StringV ignoredPlayers;

	/**
	 * @brief The percentage cutoff for player stats
	 * Percentages below this cutoff will not be shown
	*/
	double playerCutoff; 

	/**
	 * @brief The percentage cutoff for character stats
	 * Percentages below this cutoff will not be shown
	*/
	double charCutoff;

	/**
	 * @brief Whether online matches only is enabled
	*/
	bool onlineMatchesOnly;

	/**
	 * @brief Whether printing review messages is enabled
	*/
	bool printReviewMessages;

	/**
	 * @return The path to the folder containing the desired replays
	*/
	std::string getReplayPath();

	/**
	 * @return The character stats for the top players
	*/
	StringStatListPairV getPlayerSpecificCharStats(const MatchList& fullMatchList);
};

