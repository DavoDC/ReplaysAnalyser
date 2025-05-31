#pragma once

// Fighter.h

#include "Common.h"
#include "AliasHandler.h"

/**
 * @brief Represents a player controlling a character
 */
class Fighter
{
public:

	/**
	 * @brief Construct an empty Fighter
	*/
	Fighter();

	/**
	 * @brief Constructs a Fighter from a given string
	 * @param A fighter 'pair' string. e.g. 'davo1776 (Wario)'
	*/
	explicit Fighter(const std::string& rawPairS);

	/**
	 * @return The player's name
	*/
	const std::string getPlayer() const;

	/**
	 * @return The character's name
	*/
	const std::string getChar() const;

	/**
	 * @return A string representation of this Fighter
	*/
	std::string toString() const;

private:

	/**
	 * @brief The underlying data structure
	 * @brief A player string paired to a character string
	*/
	StringPair fPair;

	/**
	 * @brief The pair separator string
	*/
	static inline const std::string pairSep = "###$###";
};

