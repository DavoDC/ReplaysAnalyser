#pragma once

// Common.h
// Global libraries, macros and helper functions

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <format>


// String vector macro
using StringV = std::vector<std::string>;

// String pair macro
using StringPair = std::pair<std::string, std::string>;

// String+StatList pair macro
class StatList; // Forward declaration (needed to avoid cyclic dependency)
using StringStatListPair = std::pair<std::string, StatList>;

// Vector of StringStatListPair macro
using StringStatListPairV = std::vector<StringStatListPair>;


/**
 * @param s The string to print
 * @param useEndl End line toggle (default: false)
*/
void print(const std::string& s, bool useEndl = false);


/**
 * @brief Warn the user of an issue
 * @param desc A description of the issue
 * @param details The details of the issue
*/
void warn(const std::string& desc, const std::string& details);


/**
 * @brief Split a string into parts
 * @param full The full string
 * @param sep Substring that separates parts of the string 
 * @return The parts of the string as a vector
*/
StringV split(const std::string& full, const std::string& sep);


/**
 * @brief Same as split() but checks number of parts
 * @param exp The expected number of parts
*/
StringV split(const std::string& full, const std::string& sep, const int& exp);


/**
 * @brief Replace all instances of a given substring with another substring
 * @param source The original string (will be modified)
 * @param from The substring to replace
 * @param to The string to be substituted in
*/
void replaceAll(std::string& source, 
	const std::string& from, const std::string& to);


/**
 * @return true if s1 contains s2
*/
bool contains(const std::string& s1, const std::string& s2);


/**
 * @return true if the string vector contains the given string
*/
bool vecContains(const StringV& list, const std::string& query);


/**
 * @return true if the strings are equal, ignoring case.
*/
bool equalsIgnoreCase(const std::string& s1, const std::string& s2);