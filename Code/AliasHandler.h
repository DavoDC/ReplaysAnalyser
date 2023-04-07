#pragma once

// AliasHandler.h
// Handle player aliases

// Include common
#include "Common.h"

// Alias macro (pairs one string to multiple strings)
#define Alias std::pair<std::string, stringV>


// Declare AliasHandler class
class AliasHandler
{
public:

	// Default Constructor
	AliasHandler();

	// # Public methods
	std::string handlePlayer(std::string);

private:
	// # Private fields
	std::vector<Alias> aliases;

	// # Private methods (internal helper functions)
	void addAlias(std::string, stringV);
	void addSingleAlias(std::string, std::string);
};

