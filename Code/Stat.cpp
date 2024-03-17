// Stat.cpp : 
// Defines Stat class

// Header file
#include "Stat.h"

// Namespace mods
using namespace std;

// Default Constructor
Stat::Stat()
{
}

// Construct a statistics object
Stat::Stat(double percentage, VCPair vcPair, StringPair dateRange)
{
	this->percentage = to_string(percentage).erase(4) + "%";
	this->variantValue = vcPair.first;
	this->variantCount = to_string(vcPair.second);
	this->oldestDate = dateRange.first;
	this->newestDate = dateRange.second;
}

// ### Getters
std::string Stat::getPercentage() const
{
	return percentage;
}

std::string Stat::getVariantValue() const
{
	return variantValue;
}

std::string Stat::getVariantCount() const
{
	return variantCount;
}

std::string Stat::getOldestDate() const
{
	return oldestDate;
}

std::string Stat::getNewestDate() const
{
	return newestDate;
}