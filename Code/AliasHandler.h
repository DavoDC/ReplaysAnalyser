#pragma once

// AliasHandler.h
// Handle player aliases

// Include common
#include "Common.h"

// Alias macro (pairs one string to multiple strings)
#define Alias std::pair<std::string, StringV>


// Declare AliasHandler class
class AliasHandler
{
public:

	// Default Constructor
	AliasHandler();

	// # Public methods
	static void setOfflinePlayerAliases(std::string, std::string);
	std::string handlePlayer(std::string);

	// # Constant
	static const std::string ANON;

private:
	// # Private fields
	std::vector<Alias> aliases;
	static std::string p1Alias;
	static std::string p2Alias;

	// # Private methods (internal helper functions)
	void addAlias(std::string, StringV);
	void addSingleAlias(std::string, std::string);
};

