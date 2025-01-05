#pragma once

// Match.h

#include "Common.h"
#include "Date.h"
#include "FighterList.h"

/**
 * @brief Models a SSF2 match
 */
class Match
{
public:

	/**
	 * @brief Construct an empty match
	*/
	Match();

	/**
	 * @brief Construct a match from a raw replay path
	 * @param e.g. "../Sample_Data/1.3.1.1/2021-08-24 11.44 AM - ..."
	*/
	explicit Match(const std::string&);

	/**
	 * @return The year the match was played as an int
	*/
	int getYear();

	/**
	 * @return The year the match was played as a string
	*/
	std::string getYearS();

	/**
	 * @return The date the match was played
	*/
	const Date getDate() const;

	/**
	 * @return The date the match was played as a string
	*/
	std::string getDateS();

	/**
	 * @return True if this was an online match
	*/
	bool isOnlineMatch();
	
	/**
	 * @return The game version this match was played on
	*/
	std::string getVersion();

	/**
	 * @return A list of the Fighter pairs involved in the match
	*/
	FighterList getFighters();

	/**
	 * @return A string representation of this match
	*/
	std::string toString();

	/**
	 * @return True if this match is newer than the one inputted
	*/
	const bool isMatchNewer(const Match& mInput) const;


private:

	/**
	 * @brief The SSF2 version the match was played on (e.g. 1.3.1.2)
	*/
	std::string version;

	/**
	 * @brief The date the match was played
	*/
	Date date;

	/**
	 * @brief True if this match was played online
	*/
	bool onlineMatch;

	/**
	 * @brief A list of the Fighter pairs involved in the match
	*/
	FighterList fighters;
};

