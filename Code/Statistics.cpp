// Statistics.cpp : 
// Defines Statistics class

// Header file
#include "Statistics.h"

// Namespace mods
using namespace std;

// Default Constructor
Statistics::Statistics() : mlRef(MatchList()) 
{

}

// Construct a statistics object
Statistics::Statistics(const std::string name, const MatchList& mlRef, const Extractor matchProp)
	: name(name), mlRef(mlRef), matchProp(matchProp)
{
	// TODO
}

// TODO

