#pragma once

// MatchList.h
// Models a list of SSF2 matches

#include "Common.h"
#include "Match.h"
#include <functional>
#include <filesystem>
#include <algorithm>
#include <set>

// Returns true if the match contains a given variant
#define VarMatchChecker std::function<bool(Match)>

// Macro for long iterator type
#define FSIterator fs::recursive_directory_iterator


class MatchList
{
public:

	/**
	 * @brief Construct an empty MatchList
	*/
	MatchList();

	/**
	 * @brief Construct a MatchList from a directory path
	 * @param path The folder path with version folders and replays
	 * @param online Whether only online matches are wanted
	*/
	MatchList(std::string path, bool online);

	/**
	 * @brief Print all Matches as strings
	*/
	void printInfo();

	/**
	 * @return The number of matches in the list
	*/
	int getSize();

	/**
	 * @return The number of matches in the list as a string
	*/
	std::string getSizeS();

	/**
	 * @return The date of the last match
	*/
	Date getLastMatchDate();

	/**
	 * @return The date of the first match
	*/
	Date getFirstMatchDate();

	/**
	 * @return The underlying match list
	*/
	std::vector<Match> getMatches();

	/**
	 * @param The desired year as a string
	 * @return All matches played during a given year
	*/
	std::vector<Match> getYearMatches(std::string year);

	/**
	 * @param The desired character
	 * @return All matches involving that character
	*/
	std::vector<Match> getCharMatches(std::string character);

	/**
	 * @param The desired player's standard name
	 * @return All matches involving that player
	*/
	std::vector<Match> getPlayerMatches(std::string player);

	/**
	 * @param The desired version as a string
	 * @return All matches played on a certain version
	*/
	std::vector<Match> getVersionMatches(std::string version);

private:

	/**
	 * @brief The underlying data structure
	*/
	std::vector<Match> matches;

	/**
	 * @brief A helper method for getting certain matches
	 * @param A function that returns true if the match has the variant
	 * @return All matches with a certain variant
	*/
	std::vector<Match> getVariantMatches(VarMatchChecker f);
};