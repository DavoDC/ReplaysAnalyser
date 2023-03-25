#pragma once

// Common.h
// Project-wide essentials

// Libraries
#include <iostream>
#include <string>
#include <vector>
#include <format>

// String vector macro
#define stringV std::vector<std::string>

// Function declarations
void print(std::string, bool useEndl = false);

stringV split(std::string, std::string);
stringV split(std::string fullS, std::string sep, int exp);

void replaceAll(std::string& source, const std::string& from, const std::string& to);
