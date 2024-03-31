#pragma once

// Common.h
// Global helper functions

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <format>


// String vector macro
#define StringV std::vector<std::string>


// String pair macro
#define StringPair std::pair<std::string, std::string>


/**
 * @param s The string to print
 * @param useEndl End line toggle (default: false)
*/
void print(std::string s, bool useEndl = false);


/**
 * @brief Warn the user of an issue
 * @param desc A description of the issue
 * @param details The details of the issue
*/
void warn(std::string desc, std::string details);


/**
 * @brief Split a string into parts
 * @param full The full string
 * @param sep Substring that separates parts of the string 
 * @return The parts of the string as a vector
*/
StringV split(std::string full, std::string sep);


/**
 * @brief Same as split() but checks number of parts
 * @param exp The expected number of parts
*/
StringV split(std::string full, std::string sep, int exp);


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
bool contains(std::string s1, std::string s2);


/**
 * @return true if the string vector contains the given string
*/
bool vecContains(StringV list, std::string query);


/**
 * @return true if the strings are equal, ignoring case.
*/
bool equalsIgnoreCase(const std::string& s1, const std::string& s2);