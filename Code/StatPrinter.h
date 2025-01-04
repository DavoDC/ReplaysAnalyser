#pragma once

// StatPrinter.h
// Handles printing of statistics information

#include "Common.h"
#include "Stat.h"
#include "StatList.h"
#include "Date.h"


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
	void printPlayerSpecCharStats(const StringStatListPairV& playerSpecCharStats);
	
private:

	/**
	 * @brief Print the heading for a statistics section
	 * @param The statistic's name
	*/
	void printHeading(const std::string& statName);

	/**
	 * @param date A given date object
	 * @param currentDate The current date object
	 * @return A string of the date and the time passed since
	*/
	std::string getDateAndTimePassed(const Date& date, const Date& currentDate);

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
	 * @return A string representing a player-specific character statistic
	 * @param charStatList The character statistics list
	 * @param pos The position/rank of the statistic
	 */
	std::string getConcisePlayerSpecCharStat(const std::vector<Stat>& charStatList, int pos);
};

