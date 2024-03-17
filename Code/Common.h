#pragma once

// Common.h
// Project-wide essentials

// Libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <format>


// Macros
#define StringV std::vector<std::string>
#define StringPair std::pair<std::string, std::string>


// Function declarations
void print(std::string, bool useEndl = false);

StringV split(std::string, std::string);
StringV split(std::string fullS, std::string sep, int exp);

void replaceAll(std::string& source, const std::string& from, const std::string& to);

bool contains(std::string, std::string);
bool vecContains(StringV, std::string);