#pragma once

// Date.h

#include "Common.h"
#include <chrono>
#include <map>

// Macro for long date type (YMD object type)
using DateM = std::chrono::year_month_day;

/**
 * @brief An extended version of std::chrono::year_month_day
 */
class Date
{

public:

	/**
	 * @brief Construct a date set to the current date
	*/
	Date();

	/**
	 * @brief Construct a date from a date string
	 * @param dateS The date as a string (default 'yyyy-mm-dd' format)
	*/
	explicit Date(const std::string& dateS);

	/**
	 * @brief Construct a date from a given YMD object
	*/
	explicit Date(const DateM&);

	/**
	 * @return The underlying YMD date object
	*/
	const DateM getYMD() const;

	/**
	 * @return The date as a string (preferred 'dd/MON/yyyy' format)
	*/
	std::string toString() const;

	/**
	 * @brief Get the time period between this date and the given one
	 * @param dateIn The given date to be compared
	 * @return The absolute time period as a string (Xy,Xm,Xd)
	*/
	const std::string getAbsTimePeriod(const Date& dateIn) const;

	/**
	 * @return The number of dates fixed as a string
	*/
	const static std::string getFixedDateCountS();

	/**
	 * @brief Print out invalid dates and their fixed versions
	*/
	const static void printFixedDates();

private:

	/**
	 * @brief The underlying YMD date object
	*/
	DateM intYMD;

	/**
	 * @brief List of fixed dates ('before and after' string pairs)
	*/
	static std::vector<StringPair> fixedDates;

	/**
	 * @return true if the given date is valid 
	*/
	const bool isValid(const DateM&);

	/**
	 * @return The given date as a string (default 'yyyy-mm-dd' format)
	*/
	const std::string toOrigString(const DateM&);

	/**
	 * @param date A date that may be invalid
	 * @param dateS The date as a string (default 'yyyy-mm-dd' format)
	 * @return A valid date
	*/
	const DateM fixDate(const DateM& date, const std::string& dateS);
};

