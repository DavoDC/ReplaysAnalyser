#pragma once

// FighterList.h

#include "Common.h"
#include "Fighter.h"

/**
 * @brief Models a list of Fighters
 */
class FighterList
{
public:

	/**
	 * @brief Construct an empty FighterList
	*/
	FighterList();

	/**
	 * @brief Construct a FighterList from strings
	 * @param rawFighterList e.g. "davo (Wario) vs Spi (Falco).ssfrec"
	 * @param replayType e.g. Versus, Versus Online, BTT etc.
	*/
	FighterList(const std::string& rawFighterList, const std::string& replayType);

	/**
	 * @return A list of the players involved
	*/
	StringV getPlayers() const;

	/**
	 * @return A list of the characters involved
	*/
	StringV getChars() const;

	/**
	 * @return The character played by a given player
	 * @param stdPlayerName The player's standardised name
	*/
	std::string getChar(const std::string& stdPlayerName) const;

	/**
	 * @return String representation of this Fighter List
	*/
	std::string toString() const;

private:

	/**
	 * @brief Underlying data structure (list of Fighters)
	*/
	std::vector<Fighter> fightersV;
};

