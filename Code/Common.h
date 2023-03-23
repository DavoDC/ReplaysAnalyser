#pragma once

// Common.h
// Project-wide essentials

// Libraries
#include <iostream>
#include <string>
#include <vector>

// Function declarations
void print(std::string, bool useEndl = false);
std::vector<std::string> split(std::string, std::string);
void replaceAll(std::string& source, const std::string& from, const std::string& to);
