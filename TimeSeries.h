#ifndef TimeSeries_H
#define TimeSeries_H
#include "PriceEntry.h"
#include <vector>
#include <fstream>

class Scrub
{
private:
	std::vector<Tick> TimeS;
public:
	Scrub();
	void readfromCSV(std::ifstream & ip);   //readfrom CSV to build up record
	Tick getentry(int n);  //return the nth entry of the time series;
	Tick & operator[] (int n); //return the nth entry of the time series;
};

#endif
