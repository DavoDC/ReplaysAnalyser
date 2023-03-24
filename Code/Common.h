#pragma once

// Common.h
// Project-wide essentials

// Libraries
#include <iostream>
#include <string>
#include <vector>
#include <format>

// Function declarations
void print(std::string, bool useEndl = false);

std::vector<std::string> split(std::string, std::string);
std::vector<std::string> split(std::string fullS, std::string sep, int exp);

void replaceAll(std::string& source, const std::string& from, const std::string& to);
