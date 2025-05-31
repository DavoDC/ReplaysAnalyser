#pragma once

// PlayerSpecStatList.h

#include "StatList.h"

/**
 * @brief A player-specific statistics list
 */
class PlayerSpecStatList : public StatList
{
public:

	/**
	 * @brief Construct an empty player-specific stats list
	 */
	PlayerSpecStatList();


	/**
	 * @brief Construct a player-specific list of statistics
	 * @param playerName The name of the player
	 * See StatList constructor for description of other parameters.
	 */
	PlayerSpecStatList(const std::string& playerName,
		const MatchList& matchList, const PropExt& propExt, const StringV& ignore,
		const double& cutoff, const MatchVExt& matchVExt);


	/**
	 * @return The name of the player to whom these statistics belong to.
	 */
	const std::string& getPlayerName() const;


	/**
	 * @return True if this stat list belongs to the given player, false otherwise.
	 */
	bool isPlayer(const std::string& playerNameIn) const;

private:

	/**
	 * @brief The name of the player to whom these statistics belong to.
	 */
	std::string playerName;
};
