#pragma once

// FighterList.h
// Models a list of fighters

#include "Common.h"
#include "Fighter.h"

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
	StringV getPlayers();

	/**
	 * @return A list of the characters involved
	*/
	StringV getChars();

	/**
	 * @return String representation of this Fighter List
	*/
	std::string toString();

private:

	/**
	 * @brief Underlying data structure (list of Fighters)
	*/
	std::vector<Fighter> fightersV;
};

