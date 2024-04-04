#pragma once

// StatPrinter.h
// Handles printing of statistics information

#include "Common.h"
#include "Stat.h"
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
	
private:

	/**
	 * @brief Print a line representing a given statistic
	*/
	void printStat(const Stat& stat);

	/**
	 * @brief Print the heading for a statistics section
	 * @param The statistic's name
	*/
	void printHeading(const std::string& statName);

	/**
	 * @brief Print out strings in columns for date statistics
	*/
	void printDateColumns(const std::string&, const std::string&, const std::string&);

	/**
	 * @brief Print out strings in columns for general statistics
	*/
	void printStatColumns(const std::string&, const std::string&,
		const std::string&, const std::string&, const std::string&);

	/**
	 * @param The first date as a string
	 * @param The second date as a string
	 * @return Two dates representing a range formatted together
	*/
	std::string formatDateRange(const std::string&, const std::string&);
};

