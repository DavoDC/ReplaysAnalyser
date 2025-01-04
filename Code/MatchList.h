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
using VarMatchChecker = std::function<bool(Match)>;

// Macro for long iterator type
using FSIterator = std::filesystem::recursive_directory_iterator;


class MatchList
{
public:

	/**
	 * @brief Construct an empty MatchList
	*/
	MatchList();

	/**
	 * @brief Construct a MatchList from a vector of matches
	 * @param matchListIn A vector of matches
	*/
	explicit MatchList(const std::vector<Match>& matchListIn);

	/**
	 * @brief Construct a MatchList from a directory path
	 * @param path The folder path with version folders and replays
	 * @param online Whether only online matches are wanted
	*/
	MatchList(const std::string& path, const bool& online);

	/**
	 * @brief Print all Matches as strings
	*/
	const void printInfo() const;

	/**
	 * @return The number of matches in the list
	*/
	const int getSize() const;

	/**
	 * @return The number of matches in the list as a string
	*/
	const std::string getSizeS() const;

	/**
	 * @return The date of the last match
	*/
	const Date getLastMatchDate() const;

	/**
	 * @return The date of the first match
	*/
	const Date getFirstMatchDate() const;

	/**
	 * @return The underlying match list
	*/
	const std::vector<Match> getMatches() const;

	/**
	 * @param The desired year as a string
	 * @return All matches played during a given year
	*/
	const std::vector<Match> getYearMatches(const std::string& year) const;

	/**
	 * @param The desired character
	 * @return All matches involving that character
	*/
	const std::vector<Match> getCharMatches(const std::string& character) const;

	/**
	 * @param The desired player's standard name
	 * @return All matches involving that player
	*/
	const std::vector<Match> getPlayerMatches(const std::string& player) const;

	/**
	 * @param The desired version as a string
	 * @return All matches played on a certain version
	*/
	const std::vector<Match> getVersionMatches(const std::string& version) const;

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
	const std::vector<Match> getVariantMatches(const VarMatchChecker& f) const;
};