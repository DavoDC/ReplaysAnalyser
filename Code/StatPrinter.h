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
	 * @brief Print the heading for a statistics section
	 * @param The statistic's name
	*/
	void printHeading(const std::string& statName);

	/**
	 * @brief Print out info strings in evenly spaced columns
	*/
	void printColumns(const std::string&, const std::string&,
		const std::string&, const std::string&, const std::string&, const std::string&);

	/**
	 * @param date A given date object
	 * @param currentDate The current date object
	 * @return A string of the date and the time passed since
	*/
	std::string getDateAndTimePassed(const Date& date, const Date& currentDate);
};

