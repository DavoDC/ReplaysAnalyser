#pragma once

// AliasHandler.h
// Handle player aliases

#include "Common.h"

// Represents a standard name paired with aliases
#define Alias std::pair<std::string, StringV>

class AliasHandler
{
public:

	/**
	 * @brief The anonymous player's name
	*/
	static const std::string ANON;

	/**
	 * @param The P1 player's standard name
	 * @param The P2 player's standard name
	*/
	static void setOfflinePlayerNames(std::string p1Name, std::string p2Name);

	/**
	 * @param A raw/unstandardised/actual player name
	 * @return The player's standard name
	*/
	static std::string getStandardName(std::string playerName);

private:

	/**
	 * @brief The P1 player's standard name
	*/
	static std::string p1Name;

	/**
	 * @brief The P2 player's standard name
	*/
	static std::string p2Name;

	/**
	 * @brief Underlying list of aliases
	*/
	static std::vector<Alias> aliases;

	/**
	 * @brief Initialise the alias list
	*/
	static void initAliases();

	/**
	 * @brief Helper for adding aliases
	 * @param The player's standard name
	 * @param The player's aliases
	*/
	static void addAlias(std::string, StringV);

	/**
	 * @brief Helper for adding simple aliases
	 * @param The player's standard name
	 * @param The player's alias
	*/
	static void addSingleAlias(std::string, std::string);
};

