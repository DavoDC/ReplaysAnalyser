#pragma once

// StatPrinter.h

#include "Common.h"
#include "Date.h"
#include "Stat.h"
#include "StatList.h"
#include "PlayerSpecStatList.h"

/**
 * @brief Handles printing of statistical information
 */
class StatPrinter
{
public:

	/**
	 * @brief Make an empty StatPrinter
	*/
	StatPrinter();

	/**
	 * @brief Print out general date stats
	 * @param oldest The oldest match date
	 * @param newest The newest match date
	*/
	void printDateStats(const Date& oldest, const Date& newest);

	/**
	 * @brief Print out a statistics section
	 * @param statName The name of the statistic
	 * @param statList The list of statistics
	*/
	void printStatsList(const std::string& statName, const std::vector<Stat>& statList);

	/**
	 * @brief Print out the player-specific character statistics section
	 * @param playerSpecCharStats The player-specific character statistics
	*/
	void printPlayerSpecCharStats(const std::vector<PlayerSpecStatList>& playerSpecCharStats);

	/**
	 * @brief Print out review messages for players
	 * @param playerStats The list of player statistics
	 * @param playerSpecCharStats The player-specific character statistics
	*/
	void printPlayerReviewMessages(const std::vector<Stat>& playerStats,
		const std::vector<PlayerSpecStatList>& playerSpecCharStats);
	
private:

	/**
	 * @brief Print the heading for a statistics section
	 * @param The statistic's name
	*/
	void printHeading(const std::string& statName);

	/**
	 * @param date A given date object
	 * @param currentDate The current date object
	 * @param addAgo Whether to add "ago" to the time passed part (Default: false)
	 * @return A string of the date and the time passed since
	*/
	std::string getDateAndTimePassed(const Date& date, const Date& currentDate, bool addAgo = false);

	/**
	 * @brief Print out info strings in evenly spaced columns
	*/
	void printColumns(const std::string&, const std::string&, const std::string&,
		const std::string&, const std::string&, const std::string&, const std::string&);

	/**
	 * @brief Print out info strings in evenly spaced columns, specifically for player-specific character stats
	*/
	void printPlayerSpecCharStatCol(const std::string&, const std::string&, const std::string&,
		const std::string&, const std::string&);

	/**
	 * @brief Returns the ordinal suffix for a given integer (e.g., "st", "nd", "rd", "th").
	 *
	 * @param n The integer for which to determine the ordinal suffix.
	 * @return std::string The appropriate ordinal suffix ("st", "nd", "rd", or "th").
	 */
	std::string ordinal(int n);
};

