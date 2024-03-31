#pragma once

// Date.h
// An extended version of std::chrono::year_month_day

#include "Common.h"
#include <chrono>

// Macro for long date type (YMD object type)
#define DateM std::chrono::year_month_day


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
	Date(std::string dateS);

	/**
	 * @brief Construct a date from a given YMD object
	*/
	Date(DateM);

	/**
	 * @return The underlying YMD date object
	*/
	DateM getYMD();

	/**
	 * @return The date as a string (preferred 'dd/MON/yyyy' format)
	*/
	std::string toString();

	/**
	 * @brief Get the time period between this date and the given one
	 * @param dateIn The given date to be compared
	 * @return The absolute time period as a string (Xy,Xm,Xd)
	*/
	std::string getAbsTimePeriod(Date dateIn);

private:

	/**
	 * @brief The underlying YMD date object
	*/
	DateM intYMD;

	/**
	 * @return true if the given date is valid 
	*/
	bool isValid(DateM);

	/**
	 * @return The given date as a string (default 'yyyy-mm-dd' format)
	*/
	std::string toOrigString(DateM);

	/**
	 * @param date A date that may be invalid
	 * @param dateS The date as a string (default 'yyyy-mm-dd' format)
	 * @return A valid date
	*/
	DateM fixDate(DateM date, std::string dateS);
};

