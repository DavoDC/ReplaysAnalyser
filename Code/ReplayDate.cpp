// ReplayDate.cpp : 
// Defines ReplayDate class

// Header file
#include "ReplayDate.h"

// Namespace mods
using namespace std;


// Default Constructor
ReplayDate::ReplayDate()
{
	// Nothing needed
}


// Construct a date from a string
ReplayDate::ReplayDate(string rawDateS)
{
	
	print("ello!", true); 
	
	// 2021-01-11 1.29 PM	

	vector<string> dateParts1 = split(rawDateS, " ");


	// TEST PRINT
	for (string s : dateParts1)
	{
		print(s);
	}


	chrono::year y = chrono::year(2021);
	chrono::month m;
	chrono::day d;


	chrono::year_month_day ob = chrono::year_month_day(y, m, d);

	internalDate = ob;
}


// Extract internal date
std::chrono::year_month_day ReplayDate::getDate()
{
	return internalDate;
}